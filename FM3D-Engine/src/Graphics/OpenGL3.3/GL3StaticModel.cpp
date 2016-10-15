#include <Engine.h>

namespace ENGINE_NAME {

	bool GL3StaticModel::Initialize(int vertexCount, int indicesCount, Index* indices, VertexData* vertices) {
		m_indicesCount = indicesCount;
		GLErrorCheck();
		GLCall(glGenVertexArrays(1, &m_vao));

		glGenBuffers(1, &m_vboModel);
		GLErrorCheck();

		glBindVertexArray(m_vao);
		GLErrorCheck();
		glBindBuffer(GL_ARRAY_BUFFER, m_vboModel);
		GLErrorCheck();
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(VertexData), vertices, GL_STATIC_DRAW);
		GLErrorCheck();

		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_VERTEX_INDEX);
		GLErrorCheck();
		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_UV_INDEX);
		GLErrorCheck();
		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_NORMAL_INDEX);
		GLErrorCheck();

		glVertexAttribPointer(GL3STATICMODEL_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)0);
		GLErrorCheck();
		glVertexAttribPointer(GL3STATICMODEL_SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, uv)));
		GLErrorCheck();
		glVertexAttribPointer(GL3STATICMODEL_SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, normal)));
		GLErrorCheck();

		glGenBuffers(1, &m_vboInstance);
		GLErrorCheck();

		glBindBuffer(GL_ARRAY_BUFFER, m_vboInstance);
		GLErrorCheck();
		glBufferData(GL_ARRAY_BUFFER, m_indicesCount * sizeof(InstanceData), 0, GL_DYNAMIC_DRAW);
		GLErrorCheck();

		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_MODEL_INDEX);
		GLErrorCheck();
		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_MODEL_INDEX + 1);
		GLErrorCheck();
		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_MODEL_INDEX + 2);
		GLErrorCheck();
		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_MODEL_INDEX + 3);
		GLErrorCheck();
		glEnableVertexAttribArray(GL3STATICMODEL_SHADER_COLOR_INDEX);
		GLErrorCheck();

		GLCall(glVertexAttribPointer(GL3STATICMODEL_SHADER_MODEL_INDEX, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)0));
		GLCall(glVertexAttribPointer(GL3STATICMODEL_SHADER_MODEL_INDEX + 1, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)(sizeof(Vector4f))));
		GLCall(glVertexAttribPointer(GL3STATICMODEL_SHADER_MODEL_INDEX + 2, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)(2 * sizeof(Vector4f))));
		GLCall(glVertexAttribPointer(GL3STATICMODEL_SHADER_MODEL_INDEX + 3, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)(3 * sizeof(Vector4f))));
		GLCall(glVertexAttribPointer(GL3STATICMODEL_SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(InstanceData), (const GLvoid*)(offsetof(InstanceData, color))));
										
		GLCall(glVertexAttribDivisor(GL3STATICMODEL_SHADER_MODEL_INDEX, 1));
		GLCall(glVertexAttribDivisor(GL3STATICMODEL_SHADER_MODEL_INDEX + 1, 1));
		GLCall(glVertexAttribDivisor(GL3STATICMODEL_SHADER_MODEL_INDEX + 2, 1));
		GLCall(glVertexAttribDivisor(GL3STATICMODEL_SHADER_MODEL_INDEX + 3, 1));
		GLCall(glVertexAttribDivisor(GL3STATICMODEL_SHADER_COLOR_INDEX, 1));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		GLErrorCheck();

		glGenBuffers(1, &m_ibo);
		GLErrorCheck();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		GLErrorCheck();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(Index), indices, GL_STATIC_DRAW);
		GLErrorCheck();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		GLErrorCheck();

		glBindVertexArray(0);
		GLErrorCheck();

		return true;
	}

	void GL3StaticModel::Shutdown() {
		glDeleteBuffers(1, &m_ibo);
		GLErrorCheck();
		glDeleteBuffers(1, &m_vboModel);
		GLErrorCheck();
		glDeleteBuffers(1, &m_vboInstance);
		GLErrorCheck();
		glDeleteVertexArrays(1, &m_vao);
		GLErrorCheck();
	}

	void GL3StaticModel::Render(GLsizei instanceCount) const {
		glDrawElementsInstanced(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL, instanceCount);
		GLErrorCheck();
	}

	void GL3StaticModel::Bind() const {
		glBindVertexArray(m_vao);
		GLErrorCheck();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		GLErrorCheck();
	}

	void GL3StaticModel::BindInstanceVBO() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboInstance));
	}

	void GL3StaticModel::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		GLErrorCheck();
		glBindVertexArray(0);
		GLErrorCheck();
	}
}