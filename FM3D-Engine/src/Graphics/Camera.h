#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Camera {
	private:
		Vector3f m_position;
		Vector3f m_rotation;
		float m_zoom;
	public:
		Camera(Vector3f& position = Vector3f(0.0f, 0.0f, 0.0f), Vector3f& rotation = Vector3f(0.0f, 0.0f, 0.0f), float zoom = 1.0f);

		Matrix4f GetViewMatrix() const;

		inline Vector3f& GetPosition() { return m_position; }
		inline Vector3f& GetRotation() { return m_rotation; }
		inline float& GetZoom() { return m_zoom; }

		inline const Vector3f& GetPosition() const { return m_position; }
		inline const Vector3f& GetRotation() const { return m_rotation; }
		inline const float& GetZoom() const { return m_zoom; }
	};
}