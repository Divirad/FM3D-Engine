#pragma once
#include <Engine.h>

#define GL4RENDERER2D_MAX_SPRITES	60000
#define GL4RENDERER2D_SPRITE_SIZE	sizeof(VertexData) * 4
#define GL4RENDERER2D_BUFFER_SIZE	GL3RENDERER2D_SPRITE_SIZE * GL3RENDERER2D_MAX_SPRITES
#define GL4RENDERER2D_INDICES_SIZE	GL3RENDERER2D_MAX_SPRITES * 6
#define GL4RENDERER2D_MAX_TEXTURES	32 - 1
		  
#define GL4RENDERER2D_SHADER_VERTEX_INDEX	0
#define GL4RENDERER2D_SHADER_UV_INDEX		1
#define GL4RENDERER2D_SHADER_TID_INDEX		2
#define GL4RENDERER2D_SHADER_COLOR_INDEX	3

namespace ENGINE_NAME {

	class ENGINE_DLL GL4Renderer2D : public Renderer2D {
	private:
		struct VertexData {
			Vector3f vertex;
			Vector2f uv;
			float tid;
			unsigned int color;
		};

		class ENGINE_DLL Shader2D : public GL3Shader {
		private:
			GLint loc_prMatrix;
			GLint loc_tex;
			GLint loc_texBits;
		public:
			Shader2D(const char* vertPath, const char* fragPath) : GL3Shader(vertPath, fragPath) { GetAllUniformLocations(); };

			void Init(Matrix4f prm) {

				for (int i = 0; i <= GL4RENDERER2D_MAX_TEXTURES; i++)
					SetUniform1i(loc_tex + i, i);
				SetUniformMat4(loc_prMatrix, prm);
			}

			void LoadTexBits(int bit, int i) {
				SetUniform1i(loc_texBits + i, bit);
			}
		protected:
			void GetAllUniformLocations() {
				loc_prMatrix = GetUniformLocation("pr_matrix");
				loc_tex = GetUniformLocation("tex");
				loc_texBits = GetUniformLocation("texBits");
			};
			void BindAttributes() {};
		};

		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;
		Shader2D* m_shader;
		GLsizei m_indicesCount;
		VertexData* m_buffer;
		std::vector<const GL3Texture*> m_TextureSlots;
	public:
		GL4Renderer2D(const RenderTarget2D* renderTarget);
		~GL4Renderer2D();

		void Begin() override;
		void Submit(Quad* quad) override;
		void End() override;
		void Flush() override;

		void DrawString(const Text& text, const Vector3f& position) override;
	private:
		float SubmitTexture(const GL3Texture* texture);
	};
}