#include <Engine.h>

using namespace std;

namespace FM3D {
	Input::Input() : lastposinst(Vector2f::Zero()) {}
	Input::~Input() {}

	void Input::KeyPressed(WPARAM wParam) {

		if (m_pressed[wParam] != true) {
			m_pressed[wParam] = true;
			//cout << "INPUT:: K  :: >>" << wParam << "<< ACTIVATED\n";
		}
	}
	void Input::KeyReleased(WPARAM wParam) {
		m_pressed[wParam] = false;
		//cout << "INPUT:: K  :: >>" << wParam << "<< DEACTIVATED\n";
	}

	void Input::MPressed(LPARAM lParam, int LorR) {
		m_mousekey[LorR].clicked = ACTIVATED;
		m_mousekey[LorR].lastposclick = Vector2f(LOWORD(lParam), HIWORD(lParam));
		//cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << m_mousekey[LorR].lastposclick <<" ACTIVATED\n";
	}

	void Input::MReleased(LPARAM lParam, int LorR) {
		m_mousekey[LorR].clicked = RELEASED;
		m_mousekey[LorR].lastposclick = Vector2f(LOWORD(lParam), HIWORD(lParam));
		//cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << m_mousekey[LorR].lastposclick << "<< RELEASED\n";
	}

	void Input::MWheel(short wheeldata) {
		wheel = wheeldata;
		//cout << "INPUT:: W  :: " << wheeldata << "-Wheeldata";
	}

	void Input::MMove(LPARAM lParam) {
		lastposinst.x = static_cast<float>(GET_X_LPARAM(lParam));
		lastposinst.y = static_cast<float>(GET_Y_LPARAM(lParam));
	}

	void Input::SetMKey(int ID, KEYCLICK tof) {
		m_mousekey[ID].clicked = tof;
	}

	bool Input::CheckKey(int keyid) {
		if (m_pressed[keyid] == true) {
			return  true;
		}
		else { return false; }
	}

	bool Input::CheckMouse(int keyid) {
		if (m_mousekey[keyid].clicked == KEYCLICK::ACTIVATED)return	true;
		else return false;

	}

	void Input::DoIfKeyPressed(int keyid, void(*f)()) {

		if (m_pressed[keyid] == true) {
			(*f)();
		}
	}

	void Input::SetKey(int ID, bool tof)		//trueorFalse
	{
		m_pressed[ID] = tof;
	}

}