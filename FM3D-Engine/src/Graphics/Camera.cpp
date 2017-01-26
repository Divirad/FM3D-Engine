#include <Engine.h>

namespace FM3D {

	Camera::Camera(Vector3f& position, Vector3f& rotation, float zoom):
	m_position(position), m_rotation(rotation), m_zoom(zoom), fpstat(0){

	}

	Matrix4f Camera::GetViewMatrix() const {
		return Matrix4f::Invert(Matrix4f::Transformation(m_position * 100.0f, Vector3f(m_zoom, m_zoom, m_zoom), m_rotation));
	}

	void Camera::Preset(PRESET pre, bool showcursor) {
		Window *win = Window::GetInstance();
		Vector2i CenterCursor(win->GetWinPos() + (win->GetWinSize() / 2));
		std::cout << "Diplaycount" << ShowCursor(false);
		if (showcursor) {
			ShowCursor(true);
		}else{ ShowCursor(false); }

		switch (pre)
		{
		case FIRSTPERSON:
		{	
			//if (INPUT->CheckIfMouseIsPressed(MOUSE_LEFT) == true) { FP_pres(1.0f); }
			FP_pres(1.0f);
			break;
		}
		default:
		break;
		}

	}

	void Camera::FP_pres(float percent) {

		//Vector2f mousePos = INPUT->GetLastposInst();// .Subtract(last);
			//last = INPUT->GetLastposInst();
			//m_rotation = m_rotation.Subtract(Vector3f(dif.y, dif.x, 0.0f));
		tagPOINT mp;
		GetCursorPos(&mp);
		ScreenToClient(((Win32Window*)Window::GetInstance())->GetHWND(), &mp);
		Vector2f mousePos(mp.x, mp.y);
		Vector2f center = Vector2f(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
		center *= 0.5f;
		Vector2f dif = Vector2f::Subtract(mousePos, center);
		std::cout << "Mouse: " << dif << std::endl;
		dif *= -0.3f;
		m_rotation.y += dif.x;
		m_rotation.x += dif.y;

		//Set Mouse to Center
		tagPOINT p;
		p.x = Window::GetInstance()->GetWidth() / 2;
		p.y = Window::GetInstance()->GetHeight() / 2;
		ClientToScreen(((Win32Window*)Window::GetInstance())->GetHWND(), &p);
		SetCursorPos(p.x, p.y);
	}
}