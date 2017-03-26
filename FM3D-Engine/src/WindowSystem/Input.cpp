#include <Engine.h>

using namespace std;

namespace FM3D {
	Input::Input() : lastposinst(Vector2f::Zero()) {}

	void Input::KeyPressed(uint key) {

		if (m_pressed[key] != true) {
			m_pressed[key] = true;
			//cout << "INPUT:: K  :: >>" << wParam << "<< ACTIVATED\n";
		}
	}
	void Input::KeyReleased(uint key) {
		m_pressed[key] = false;
		//cout << "INPUT:: K  :: >>" << wParam << "<< DEACTIVATED\n";
	}

	void Input::MPressed(float x, float y, int button) {
		m_mousekey[button].pressed = true;
		m_mousekey[button].lastposclick = Vector2f(x, y);
		//cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << m_mousekey[LorR].lastposclick <<" ACTIVATED\n";
	}

	void Input::MReleased(float x, float y, int button) {
		m_mousekey[button].pressed = false;
		m_mousekey[button].lastposclick = Vector2f(x, y);
		//cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << m_mousekey[LorR].lastposclick << "<< RELEASED\n";
	}

	void Input::MWheel(short wheeldata) {
		wheel = wheeldata;
		//cout << "INPUT:: W  :: " << wheeldata << "-Wheeldata";
	}

	void Input::MMove(float x, float y) {
		lastposinst.x = x;
		lastposinst.y = y;
	}

	void Input::SetMKey(int ID, bool tof) {
		m_mousekey[ID].pressed = tof;
	}

	bool Input::CheckKey(int keyid) {
		return m_pressed[keyid];
	}

	bool Input::CheckMouse(int keyid) {
		return m_mousekey[keyid].pressed;

	}

	void Input::DoIfKeyPressed(int keyid, void(*f)()) {
		if (m_pressed[keyid] == true) {
			(*f)();
		}
	}

	void Input::SetKey(int ID, bool tof) {
		m_pressed[ID] = tof;
	}

}