#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3RenderTarget2D : public RenderTarget2D {
	private:
		GLuint m_frameBuffer;
		GL3Texture* m_texture;
		GLuint m_depthBuffer;
	public:
		GL3RenderTarget2D(const Vector2i& size, bool useDepth);
		~GL3RenderTarget2D();
		
		void ReSize(const Vector2i& size) override;
		void PresentOnScreen(const Vector2i& screenSize) override;
		void BindAsTarget() const override;
		void BindAsSource() const override;
		const Texture* GetTexture() override;

		std::vector<byte> GetPixelData() override;
		std::vector<byte> GetPixelDataReversed() override;	

	private:
		void Create(bool useDepth);
		void Delete();
	};
}