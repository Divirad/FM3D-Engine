#include <Engine.h>

namespace FM3D {

	Camera::Camera(Vector3f& position, Vector3f& rotation, float zoom):
	m_position(position), m_rotation(rotation), m_zoom(zoom), fpstat(0), last(Vector2f::Zero()){

	}

	Matrix4f Camera::GetViewMatrix() const {
		//const float DEG2RAD = 3.141593f / 180;
		//float sx, sy, sz, cx, cy, cz, theta;

		//// rotation angle about X-axis (pitch)
		//theta = m_rotation.x * DEG2RAD;
		//sx = sinf(theta);
		//cx = cosf(theta);

		//// rotation angle about Y-axis (yaw)
		//theta = m_rotation.y * DEG2RAD;
		//sy = sinf(theta);
		//cy = cosf(theta);

		//// rotation angle about Z-axis (roll)
		//theta = m_rotation.z * DEG2RAD;
		//sz = sinf(theta);
		//cz = cosf(theta);

		//// determine left axis
		//Vector3f left(cy*cz,
		//sx*sy*cz + cx*sz,
		//-cx*sy*cz + sx*sz);

		//// determine up axis
		//Vector3f up(-cy*sz,
		//	-sx*sy*sz + cx*cz,
		//	cx*sy*sz + sx*cz);

		//// determine forward axis
		//Vector3f forward(sy,
		//-sx*cy,
		//cx*cy);

		//auto res = Matrix4f(
		//	Vector4f(left.x, up.x, forward.x, -m_position.x),
		//	Vector4f(left.y, up.y, forward.y, -m_position.y),
		//	Vector4f(left.z, up.z, forward.z, -m_position.z),
		//	Vector4f(0.0f, 0.0f, 0.0f, 1.0f));

		//std::cout << res << std::endl;
		//return res;

		auto res = Matrix4f::RotationX(-m_rotation.x) * (Matrix4f::RotationY(-m_rotation.y) * (Matrix4f::RotationZ(-m_rotation.z) * (Matrix4f::Translate(m_position * -1.0f))));
		return res;
	}

	void Camera::Preset(PRESET pre, bool showcursor) {
		Window *win = Window::GetInstance();
		Vector2i CenterCursor(win->GetWinPos() + (win->GetWinSize() / 2));
		//std::cout << "Diplaycount" << ShowCursor(false);
		if (showcursor) {
			ShowCursor(true);
		}else{ ShowCursor(false); }

		switch (pre)
		{
		case FIRSTPERSON:
		{	
			//if (INPUT->CheckIfMouseIsPressed(MOUSE_LEFT) == true) { FP_pres(1.0f); }
			if(GetFocus() != NULL)
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
		ScreenToClient(((Win32Window*)Window::GetInstance())->GetHwnd(), &mp);
		Vector2f mousePos(mp.x, mp.y);
		Vector2f center = Vector2f(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
		center *= 0.5f;
		Vector2f dif = Vector2f::Subtract(mousePos, center);
		dif *= -0.3f;
		m_rotation.y += dif.x;
		m_rotation.x += dif.y;

		//Set Mouse to Center
		tagPOINT p;
		p.x = Window::GetInstance()->GetWidth() / 2;
		p.y = Window::GetInstance()->GetHeight() / 2;
		ClientToScreen(((Win32Window*)Window::GetInstance())->GetHwnd(), &p);
		SetCursorPos(p.x, p.y);
	}
}