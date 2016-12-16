#include <Engine.h>

namespace FM3D {

	Camera::Camera(Vector3f& position, Vector3f& rotation, float zoom, bool fp):
	m_position(position), m_rotation(rotation), m_zoom(zoom), fpstat(fp){

	}

	Matrix4f Camera::GetViewMatrix() const {
		return Matrix4f::Invert(Matrix4f::Transformation(m_position * 100.0f, Vector3f(m_zoom, m_zoom, m_zoom), m_rotation));
	}

	void Camera::Preset(PRESET pre, bool showcursor) {
		Window *win = Window::GetInstance();
		Vector2i CenterCursor(win->GetWinPos() + (win->GetWinSize() / 2));

		if (showcursor) {
			ShowCursor(true);
		}else{ ShowCursor(false); }

		switch (pre)
		{
		case FIRSTPERSON:
		{
			if (fpstat == true) {
				
				SetCursorPos(CenterCursor.x, CenterCursor.y);
				before = INPUT->GetLastposInst();
                
				fpstat = false;
			}
			else {
				after = INPUT->GetLastposInst();
				Vector2f result = after.Subtract(before);
				m_rotation = Vector3f(m_rotation.x + result.y, m_rotation.y + result.x, m_rotation.z);
				fpstat = true;
			}
			break;
		}
		default:
			break;
		}
	}
}