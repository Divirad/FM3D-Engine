#include <Engine.h>

namespace ENGINE_NAME {

	bool GL3AnimatedModel::Initialize(int vertexCount, int indicesCount, Index* indices, VertexData* vertices) {
		m_indicesCount = indicesCount;
		GLErrorCheck();
		GLCall(glGenVertexArrays(1, &m_vao));

		GLCall(glGenBuffers(1, &m_vbo));

		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GLCall(glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VertexData), vertices, GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(GL3ANIMATEDMODEL_SHADER_VERTEX_INDEX));
		GLCall(glEnableVertexAttribArray(GL3ANIMATEDMODEL_SHADER_UV_INDEX));
		GLCall(glEnableVertexAttribArray(GL3ANIMATEDMODEL_SHADER_NORMAL_INDEX));
		GLCall(glEnableVertexAttribArray(GL3ANIMATEDMODEL_SHADER_BONEINDEX_INDEX));
		GLCall(glEnableVertexAttribArray(GL3ANIMATEDMODEL_SHADER_BONEWEIGHT_INDEX));

		GLCall(glVertexAttribPointer(GL3ANIMATEDMODEL_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)0));
		GLCall(glVertexAttribPointer(GL3ANIMATEDMODEL_SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, uv))));
		GLCall(glVertexAttribPointer(GL3ANIMATEDMODEL_SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, normal))));
		GLCall(glVertexAttribIPointer(GL3ANIMATEDMODEL_SHADER_BONEINDEX_INDEX, 4, GL_INT, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, boneIndex))));
		GLCall(glVertexAttribPointer(GL3ANIMATEDMODEL_SHADER_BONEWEIGHT_INDEX, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, boneWeight))));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		GLCall(glGenBuffers(1, &m_ibo));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(Index), indices, GL_STATIC_DRAW));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		GLCall(glBindVertexArray(0));

		return true;
	}

	GL3AnimatedModel::~GL3AnimatedModel() {
		GLCall(glDeleteBuffers(1, &m_ibo));
		GLCall(glDeleteBuffers(1, &m_vbo));
		GLCall(glDeleteVertexArrays(1, &m_vao));
	}

	void GL3AnimatedModel::Render() const {
		GLCall(glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL));
	}

	void GL3AnimatedModel::Bind() const {
		GLCall(glBindVertexArray(m_vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	}

	void GL3AnimatedModel::Unbind() {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		GLCall(glBindVertexArray(0));
	}
}