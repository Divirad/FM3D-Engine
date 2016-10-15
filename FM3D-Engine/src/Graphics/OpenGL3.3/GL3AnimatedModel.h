#pragma once
#include <Engine.h>

#define GL3ANIMATEDMODEL_SHADER_VERTEX_INDEX		0
#define GL3ANIMATEDMODEL_SHADER_UV_INDEX			1
#define GL3ANIMATEDMODEL_SHADER_NORMAL_INDEX		2
#define GL3ANIMATEDMODEL_SHADER_BONEINDEX_INDEX		3
#define GL3ANIMATEDMODEL_SHADER_BONEWEIGHT_INDEX	4

namespace ENGINE_NAME {

	class GL3AnimatedModel : public AnimatedModel {
	private:
		GLuint m_vao, m_vbo, m_ibo;

		friend class GL3RenderSystem;
		friend class GL4RenderSystem;
		GL3AnimatedModel() {}
		~GL3AnimatedModel();
	public:
		bool Initialize(int vertexCount, int indicesCount, Index* indices, VertexData* vertices) override;

		void Bind() const;
		static void Unbind();
		void Render() const;
	};
}