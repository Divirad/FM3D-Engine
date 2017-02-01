#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL RenderTarget2D {
	protected:
		Vector2i m_size;

		RenderTarget2D(const Vector2i& size);
	public:
		virtual void ReSize(const Vector2i& size) = 0;
		virtual void PresentOnScreen(const Vector2i& screenSize) = 0;
		virtual void BindAsTarget() const = 0;
		virtual void BindAsSource() const = 0;
		virtual std::shared_ptr<const Texture> GetTexture() = 0;

		int GetWidth() const;
		int GetHeight() const;

		virtual std::vector<byte> GetPixelData() = 0;
	};
}