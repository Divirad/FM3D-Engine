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
	};
}