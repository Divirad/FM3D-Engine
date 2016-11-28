#pragma once
#include <Engine.h>

#define GL3RENDERER2D_MAX_SPRITES	60000
#define GL3RENDERER2D_SPRITE_SIZE	sizeof(VertexData) * 4
#define GL3RENDERER2D_BUFFER_SIZE	GL3RENDERER2D_SPRITE_SIZE * GL3RENDERER2D_MAX_SPRITES
#define GL3RENDERER2D_INDICES_SIZE	GL3RENDERER2D_MAX_SPRITES * 6
#define GL3RENDERER2D_MAX_TEXTURES	32 - 1

#define GL3RENDERER2D_SHADER_VERTEX_INDEX	0
#define GL3RENDERER2D_SHADER_UV_INDEX		1
#define GL3RENDERER2D_SHADER_COLOR_INDEX	2

namespace FM3D {

	class ENGINE_DLL GL3Renderer2D : public Renderer2D {
	private:
		struct VertexData {
			Vector3f vertex;
			Vector2f uv;
			unsigned int color;
		};

		class Shader2D;

		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ibo;
		Shader2D* m_shader;
		GLsizei m_indicesCount;
		VertexData* m_buffer;
		const GL3Texture* m_texture;
	public:
		GL3Renderer2D(const RenderTarget2D* renderTarget);
		~GL3Renderer2D();

		void Begin() override;
		void Submit(Quad* quad) override;
//		void Submit(BasicItem2D* quad) override;
		void End() override;
		void Flush() override;

		void DrawString(const Text& text, const Vector3f& position) override;
	};
}