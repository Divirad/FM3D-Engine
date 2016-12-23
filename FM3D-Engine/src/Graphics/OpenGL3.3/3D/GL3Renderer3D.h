#pragma once
#include <Engine.h>

#define GL3RENDERER3D_MAXTEXTURES 32
#define GL3RENDERER3D_MAX_BONES 120

namespace FM3D {

	class ENGINE_DLL GL3Renderer3D : Renderer3D {
	private:
		Matrix4f m_projectionMatrix;

		GL3GBuffer m_gbuffer;

		uint m_width, m_height;

		GL3DirectionalLightShader m_dirLightShader;
		GL3PointLightShader m_pointLightShader;
		GL3NullShader m_nullShader;
		GL3Shader3D m_shader3D;

		std::map<const Mesh*, std::map<const Model*, std::vector<const Entity*>>> m_meshModelEntityMap;
		std::vector<PointLight*> m_pointLights;

		GL3Mesh* m_bsphere;
		GL3Mesh* m_quad;

		friend class GL3RenderSystem;
		friend class GL4RenderSystem;
		GL3Renderer3D(Matrix4f& projectionMatrix, uint width, uint height, GL3RenderSystem* renderSystem, RenderTarget2D* target);
	public:
		void Submit(const Entity* e) override;
		void Flush(const Matrix4f& viewMatrix, const Vector3f& cameraPos) override;
		void SetProjectionMatrix(const Matrix4f& projectionMatrix) override;
	private:
		void GeometryPass(const Matrix4f& viewMatrix);
		void StencilPass(PointLight& light, Matrix4f& wvp);
		void PointLightPass(PointLight& light, const Matrix4f& viewProjMatrix, const Vector3f& cameraPos);
		void DirectionalLightPass(const Vector3f cameraPos);
		void FinalPass();
	};
}