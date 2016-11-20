#include <Engine.h>

namespace ENGINE_NAME {

	Camera::Camera(Vector3f& position, Vector3f& rotation, float zoom):
	m_position(position), m_rotation(rotation), m_zoom(zoom) {

	}

	Matrix4f Camera::GetViewMatrix() const {
		return Matrix4f::Invert(Matrix4f::Transformation(m_position * 100.0f, Vector3f(m_zoom, m_zoom, m_zoom), m_rotation));
	}
}