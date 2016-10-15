#pragma once
#include <Engine.h>

#define GL3STATICMODEL_SHADER_VERTEX_INDEX		0
#define GL3STATICMODEL_SHADER_UV_INDEX			1
#define GL3STATICMODEL_SHADER_NORMAL_INDEX		2
#define GL3STATICMODEL_SHADER_MODEL_INDEX		3
#define GL3STATICMODEL_SHADER_COLOR_INDEX		7

namespace ENGINE_NAME {

	class ENGINE_DLL GL3StaticModel : public StaticModel {
	private:
		GLuint m_vao, m_vboModel, m_vboInstance, m_ibo;

		friend class GL3RenderSystem;
		friend class GL4RenderSystem;
		GL3StaticModel() {};
	public:
		bool Initialize(int vertexCount, int indicesCount, Index* indices, VertexData* vertices) override;
		void Shutdown() override;

		inline int GetIndexCount() { return m_indicesCount; }

		void Bind() const;
		void BindInstanceVBO() const;
		static void Unbind();
		void Render(GLsizei instanceCount) const;
	};
}