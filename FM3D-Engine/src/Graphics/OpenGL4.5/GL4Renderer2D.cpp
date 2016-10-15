#include <Engine.h>

namespace ENGINE_NAME {

	void GL4Renderer2D::Shutdown() {
		glDeleteBuffers(1, &m_ibo);
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		delete m_shader;
	}

	void GL4Renderer2D::SetProjectionMatrix(const Matrix4f& projectionMatrix) {
		m_shader->Bind();
		m_shader->Init(projectionMatrix);
		m_shader->Unbind();
	}

	void GL4Renderer2D::Initialize(Matrix4f projectionMatrix) {
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		GLErrorCheck();

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, GL4RENDERER2D_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		GLErrorCheck();

		glEnableVertexAttribArray(GL4RENDERER2D_SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(GL4RENDERER2D_SHADER_UV_INDEX);
		glEnableVertexAttribArray(GL4RENDERER2D_SHADER_TID_INDEX);
		glEnableVertexAttribArray(GL4RENDERER2D_SHADER_COLOR_INDEX);
		GLErrorCheck();

		glVertexAttribPointer(GL4RENDERER2D_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)0);
		glVertexAttribPointer(GL4RENDERER2D_SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, uv)));
		glVertexAttribPointer(GL4RENDERER2D_SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, tid)));
		glVertexAttribPointer(GL4RENDERER2D_SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), (const GLvoid*)(offsetof(VertexData, color)));
		GLErrorCheck();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		GLErrorCheck();
		GLuint* indices = new GLuint[GL4RENDERER2D_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < GL4RENDERER2D_INDICES_SIZE; i += 6) {
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, GL4RENDERER2D_INDICES_SIZE * sizeof(uint), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		GLErrorCheck();

		glBindVertexArray(0);
		GLErrorCheck();

		const char* vertexShaderSrc =
#include "GL4Shader2D.vert"
			;
		const char* fragmentShaderSrc =
#include "GL4Shader2D.frag"
			;

		m_shader = new Shader2D(vertexShaderSrc, fragmentShaderSrc);
		m_shader->Bind();
		m_shader->Init(projectionMatrix);
		m_shader->Unbind();
	}

	float GL4Renderer2D::SubmitTexture(const GL3Texture* texture) {
		float result = 0.0f;
		bool found = false;
		for (uint i = 0; i < m_TextureSlots.size(); i++) {
			if (m_TextureSlots[i] == texture) {
				result = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found) {
			if (m_TextureSlots.size() >= GL4RENDERER2D_MAX_TEXTURES) {
				End();
				Flush();
				Begin();
			}
			m_TextureSlots.push_back(texture);
			result = (float)(m_TextureSlots.size());
		}
		return result;
	}

	void GL4Renderer2D::Begin() {
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GL4Renderer2D::Submit(Quad* quad) {
		uint color = quad->GetColor();
		const GL3Texture* tex = (const GL3Texture*)quad->GetTexture();
		float tid = 0.0f;
		if (tex)
			tid = SubmitTexture(tex);
		else
			tid = GL4RENDERER2D_MAX_TEXTURES + 1;

		Vector3f vertex = m_transformationMatrix * quad->GetPosition0();
		m_buffer->vertex = vertex;
		m_buffer->uv = quad->GetUV0();
		m_buffer->tid = tid;
		m_buffer->color = color;
		m_buffer++;

		vertex = m_transformationMatrix * quad->GetPosition2();
		m_buffer->vertex = vertex;
		m_buffer->uv = quad->GetUV2();
		m_buffer->tid = tid;
		m_buffer->color = color;
		m_buffer++;

		vertex = m_transformationMatrix * quad->GetPosition1();
		m_buffer->vertex = vertex;
		m_buffer->uv = quad->GetUV1();
		m_buffer->tid = tid;
		m_buffer->color = color;
		m_buffer++;

		vertex = m_transformationMatrix * quad->GetPosition3();
		m_buffer->vertex = vertex;
		m_buffer->uv = quad->GetUV3();
		m_buffer->tid = tid;
		m_buffer->color = color;
		m_buffer++;

		m_indicesCount += 6;
	}

	void GL4Renderer2D::End() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void GL4Renderer2D::Flush() {
		m_shader->Bind();
		for (uint i = 0; i < m_TextureSlots.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i] ? m_TextureSlots[i]->GetID() : GL4RENDERER2D_MAX_TEXTURES);
			m_shader->LoadTexBits(m_TextureSlots[i] ? m_TextureSlots[i]->GetBits() : 0, i);
		}

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, NULL);
		m_shader->Unbind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		GLErrorCheck();

		m_indicesCount = 0;
		m_TextureSlots.clear();
	}

	void GL4Renderer2D::DrawString(const Text& text, const Vector3f& position) {
		float ts = 0.0f;
		ts = SubmitTexture(((GL3Texture*)text.font->getTexture()));

		const Vector2f* scale = text.font->getScale();

		float x = position.x;

		//texture_font_t* ftFont = font.GetFTFont();

		for (uint i = 0; i < text.txt.length(); i++) {
			char c = text.txt[i];
			const Character* glyph = text.font->getChar(c);
			if (glyph != NULL) {
				//if (i > 0) {
				//	float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
				//	x += kerning / scale.x;
				//}

				float x0 = x + glyph->left * scale->x;
				float y0 = position.y + glyph->top * scale->y;
				float x1 = x0 + glyph->width * scale->x;
				float y1 = y0 - glyph->height * scale->y;

				//if (!glyph->width || !glyph->height) {

				float atlas_width = (float)text.font->getTexture()->GetWidth();
				float atlas_height = (float)text.font->getTexture()->GetHeight();
				float u0 = glyph->offsetX;
				float v0 = 0;
				float u1 = glyph->offsetX + glyph->width / atlas_width;
				float v1 = glyph->height / atlas_height;

				m_buffer->vertex = m_transformationMatrix * Vector3f(x0, y0, 0);
				m_buffer->uv = Vector2f(u0, v0);
				m_buffer->tid = ts;
				m_buffer->color = text.color;
				m_buffer++;

				m_buffer->vertex = m_transformationMatrix * Vector3f(x0, y1, 0);
				m_buffer->uv = Vector2f(u0, v1);
				m_buffer->tid = ts;
				m_buffer->color = text.color;
				m_buffer++;

				m_buffer->vertex = m_transformationMatrix * Vector3f(x1, y1, 0);
				m_buffer->uv = Vector2f(u1, v1);
				m_buffer->tid = ts;
				m_buffer->color = text.color;
				m_buffer++;

				m_buffer->vertex = m_transformationMatrix * Vector3f(x1, y0, 0);
				m_buffer->uv = Vector2f(u1, v0);
				m_buffer->tid = ts;
				m_buffer->color = text.color;
				m_buffer++;

				m_indicesCount += 6;

				x += glyph->advanceX * scale->x;
				//}
			} else {
				std::cout << "Glyph null" << std::endl;
			}
		}
	}
}