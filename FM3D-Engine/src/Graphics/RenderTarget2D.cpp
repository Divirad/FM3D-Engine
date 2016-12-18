#include <Engine.h>

namespace FM3D {

	RenderTarget2D::RenderTarget2D(const Vector2i& size): m_size(size) {

	}

	int RenderTarget2D::GetWidth() const {
		return m_size.x;
	}

	int RenderTarget2D::GetHeight() const {
		return m_size.y;
	}
}