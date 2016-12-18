#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3RenderTarget2D : public RenderTarget2D {
	private:
		GLuint m_frameBuffer;
		GLuint m_texture;
		GLuint m_depthBuffer;
	public:
		GL3RenderTarget2D(const Vector2i& size, bool useDepth);
		
		void ReSize(const Vector2i& size) override;
		void PresentOnScreen(const Vector2i& screenSize) override;
		void BindAsTarget() const override;
		void BindAsSource() const override;
		std::shared_ptr<const Texture> GetTexture() override;
	};
}