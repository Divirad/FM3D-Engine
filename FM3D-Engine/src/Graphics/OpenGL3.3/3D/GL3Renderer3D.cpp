#include <Engine.h>

namespace FM3D {

	GL3Renderer3D::GL3Renderer3D(Matrix4f& projectionMatrix, uint width, uint height, GL3RenderSystem* renderSystem, RenderTarget2D* target) :
		Renderer3D(target), m_projectionMatrix(projectionMatrix), m_gbuffer(width, height), m_width(width), m_height(height),
		m_dirLightShader(), m_pointLightShader(), m_nullShader(), m_pointLights(), m_bsphere((GL3Mesh*)MeshCreator::CreateIcosahedron(renderSystem)),
		m_quad((GL3Mesh*)MeshCreator::CreateRectangle(renderSystem, Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(2.0f, 2.0f))) {

		m_shader3D.Bind();
		m_shader3D.SetColorTextureUnit(0);

		m_pointLightShader.Bind();
		m_pointLightShader.Initialize(m_width, m_height);

		m_dirLightShader.Bind();
		m_dirLightShader.Initialize(m_width, m_height);
		m_dirLightShader.SetWVP(Matrix4f::Transpose(Matrix4f::Identity()));
		m_dirLightShader.SetDirectionalLight(DirectionalLight{ Vector3f(1.0f, 1.0f, 1.0f), 0.32f, 0.16f, Vector3f(1.0f, -1.0f, -1.0f) });
	}

	void GL3Renderer3D::SetProjectionMatrix(const Matrix4f& projectionMatrix) {
		m_projectionMatrix = projectionMatrix;
	}

	void GL3Renderer3D::Submit(const EntitySystem::Entity* e) {
		if (!e->HasComponents(std::vector<EntitySystem::ComponentId>({ PositionComponentId, RotationComponentId, ScaleComponentId, RenderableComponentId })))
			throw std::runtime_error("Entity doesn't has necessary components for rendering");
		const Model* model = static_cast<RenderableComponent*>(e->GetComponent(RenderableComponentId))->GetModel();
		const Mesh* mesh = model->GetMesh();

		std::map<const Model*, std::vector<const EntitySystem::Entity*>>& map = m_meshModelEntityMap[mesh];
		std::vector<const EntitySystem::Entity*>& vec = map[model];
		vec.push_back(e);
	}

	void GL3Renderer3D::Flush(const Matrix4f& viewMatrix, const Vector3f& cameraPos) {
		Matrix4f viewProjMatrix = m_projectionMatrix * viewMatrix;

		m_gbuffer.StartFrame();

		GeometryPass(viewMatrix);

		glEnable(GL_STENCIL_TEST);

		for (PointLight* light : m_pointLights) {
			PointLightPass(*light, viewProjMatrix, cameraPos);
		}

		glDisable(GL_STENCIL_TEST);

		DirectionalLightPass(cameraPos);

		FinalPass();
	}

	void GL3Renderer3D::GeometryPass(const Matrix4f& viewMatrix) {
		m_shader3D.Bind();

		m_gbuffer.BindForGeomPass();

		GLCall(glDepthMask(GL_TRUE));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GLCall(glEnable(GL_DEPTH_TEST));
		//GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_BACK));

		GLCall(glActiveTexture(GL_TEXTURE0));

		Matrix4f viewProjectionMatrix = m_projectionMatrix * viewMatrix;

		for (std::map<const Mesh*, std::map<const Model*, std::vector<const EntitySystem::Entity*>>>::iterator it = m_meshModelEntityMap.begin(); it != m_meshModelEntityMap.end(); ++it) {
			for (uint i = 0; i < it->first->GetCountOfParts(); i++) {
				((const GL3Mesh*)it->first)->Bind(i);
				for (std::map<const Model*, std::vector<const EntitySystem::Entity*>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
					((GL3Texture*)it2->first->GetMaterials()[i]->texture)->Bind();
					for (const EntitySystem::Entity*& e : it2->second) {
						if (it->first->IsAnimated()) {
							if (it2->first->IsAnimated()) {
								AnimatedModel* a = (AnimatedModel*)it2->first;
								if (a->GetAnimation() != nullptr) {
									std::vector<Matrix4f> bones(a->GetAnimation()->GetBonePositions(a->GetAnimationTime(), it->first->GetSkeleton()->GetOffsetMatrices()));
									m_shader3D.SetBones(bones);
								} else {
									m_shader3D.ReSetBones(it->first->GetSkeleton()->GetOffsetMatrices().size());
								}
							} else {
								m_shader3D.ReSetBones(it->first->GetSkeleton()->GetOffsetMatrices().size());
							}
						}
						const Vector3f& position = static_cast<PositionComponent*>(e->GetComponent(PositionComponentId))->GetPosition();
						const Vector3f& rotation = static_cast<RotationComponent*>(e->GetComponent(RotationComponentId))->GetRotation();
						const Vector3f& scale = static_cast<ScaleComponent*>(e->GetComponent(ScaleComponentId))->GetScale();
						Matrix4f modelMatrix = Matrix4f::Transformation(position, scale, rotation);
						m_shader3D.SetWVP(Matrix4f::Transpose(viewProjectionMatrix * (Matrix4f::Scale(Vector3f(100.0f, 100.0f, 100.0f)) * modelMatrix)));
						m_shader3D.SetWorldMatrix(Matrix4f::Transpose(modelMatrix));
						((const GL3Mesh*)it->first)->Render(i);
					}
				}
			}
			GL3Mesh::Unbind();
		}

		m_meshModelEntityMap.clear();

		// When we get here the depth buffer is already populated and the stencil pass
		// depends on it, but it does not write to it.
		GLCall(glDepthMask(GL_FALSE));
		GLCall(glDisable(GL_CULL_FACE));
	}

	void GL3Renderer3D::StencilPass(PointLight& light, Matrix4f& wvp) {
		m_nullShader.Bind();

		m_gbuffer.BindForStencilPass();
		GLCall(glEnable(GL_DEPTH_TEST));

		GLCall(glDisable(GL_CULL_FACE));

		GLCall(glClear(GL_STENCIL_BUFFER_BIT));

		GLCall(glStencilFunc(GL_ALWAYS, 0, 0));

		GLCall(glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP));
		GLCall(glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP));

		m_nullShader.SetWVP(wvp);
		m_bsphere->Bind(0);
		m_bsphere->Render(0);
		m_bsphere->Unbind();
	}

	void GL3Renderer3D::PointLightPass(PointLight& light, const Matrix4f& viewProjMatrix, const Vector3f& cameraPos) {
		float maxChannel = fmax(fmax(light.color.x, light.color.y), light.color.z);
		float scale = Math::QuadraticEquation(light.attenuation.exp, light.attenuation.linear, light.attenuation.exp - 256 * maxChannel * light.diffuseIntensity);
		Matrix4f wvp = viewProjMatrix * Matrix4f::Scale(Vector3f(scale, scale, scale)) * Matrix4f::Translate(light.position);

		StencilPass(light, wvp);

		m_gbuffer.BindForLightPass();

		m_pointLightShader.Bind();
		m_pointLightShader.SetEyeWorldPos(cameraPos);

		GLCall(glStencilFunc(GL_NOTEQUAL, 0, 0xFF));

		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendEquation(GL_FUNC_ADD));
		GLCall(glBlendFunc(GL_ONE, GL_ONE));

		GLCall(glEnable(GL_CULL_FACE));
		GLCall(glCullFace(GL_FRONT));

		m_pointLightShader.SetWVP(wvp);
		m_pointLightShader.SetPointLight(light);
		m_bsphere->Bind(0);
		m_bsphere->Render(0);
		m_bsphere->Unbind();
		GLCall(glCullFace(GL_BACK));

		GLCall(glDisable(GL_BLEND));
	}

	void GL3Renderer3D::DirectionalLightPass(const Vector3f cameraPos) {
		m_gbuffer.BindForLightPass();

		m_dirLightShader.Bind();
		m_dirLightShader.SetEyeWorldPos(cameraPos);

		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendEquation(GL_FUNC_ADD));
		GLCall(glBlendFunc(GL_ONE, GL_ONE));

		m_quad->Bind(0);
		m_quad->Render(0);
		m_quad->Unbind();

		GLCall(glDisable(GL_BLEND));
	}

	void GL3Renderer3D::FinalPass() {
		m_gbuffer.BindForFinalPass();
		m_target->BindAsTarget();
		GLCall(glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_target->GetWidth(), m_target->GetHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR));
		//m_gbuffer.DebugRendering(m_width, m_height);

	}

}