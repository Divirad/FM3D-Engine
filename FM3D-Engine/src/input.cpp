#include <Engine.h>

using namespace std;

namespace FM3D
{
	Inputsystem Inputsystem::s_instance = Inputsystem();
	Inputsystem::Inputsystem() {}
	Inputsystem::~Inputsystem() {}

	void Inputsystem::keyPressed(WPARAM wParam) {

		if (m_pressed[wParam] != true)
		{
			m_pressed[wParam] = true;
			cout << "INPUT:: K  :: >>" << wParam << "<< ACTIVATED\n";
		}
	}
	void Inputsystem::keyReleased(WPARAM wParam) {
		m_pressed[wParam] = false;
		cout << "INPUT:: K  :: >>" << wParam << "<< DEACTIVATED\n";
	}

	void Inputsystem::MPressed(LPARAM lParam, int LorR) {
		m_mousekey[LorR].clicked = ACTIVATED;
		m_mousekey[LorR].lastposclick = Vector2f(LOWORD(lParam), HIWORD(lParam));
		cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << m_mousekey[LorR].lastposclick <<" ACTIVATED\n";
	}

	void Inputsystem::MReleased(LPARAM lParam, int LorR) {
		m_mousekey[LorR].clicked = RELEASED;
		m_mousekey[LorR].lastposclick = Vector2f(LOWORD(lParam), HIWORD(lParam));
		cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << m_mousekey[LorR].lastposclick << "<< RELEASED\n";
	}

	void Inputsystem::MWheel(short wheeldata)
	{
		wheel = wheeldata;
		cout << "INPUT:: W  :: " << wheeldata << "-Wheeldata";
	}

	void Inputsystem::MMove(LPARAM lParam)
	{
		
		/*m_mousekey[MOUSE_LEFT].clicked = NOCLICK;
		m_mousekey[MOUSE_RIGHT].clicked = NOCLICK;*/
		/*
		m_mousekey[MOUSE_MIDDLE].clicked = NOCLICK;*/

			lastposinst.x = LOWORD(lParam);
			lastposinst.y = HIWORD(lParam);
			//cout << "INPUT:: INS:: Mouse @ the Coords >>X: " << LOWORD(lParam) << " AND Y: " << HIWORD(lParam) << "\n";
	}

	void Inputsystem::setMKey(int ID, KEYCLICK tof)
	{
		m_mousekey[ID].clicked = tof;
	}

	bool Inputsystem::CheckIfKeyIsPressed(int keyid)
	{
		if (m_pressed[keyid] == true)
		{
			return  true;
		}
		else { return false; }
	}

	Inputsystem::KEYCLICK Inputsystem::CheckIfMouseIsPressed(int keyid)
	{
		return	m_mousekey[keyid].clicked;

	}

	void Inputsystem::DoIfKeyPressed(int keyid, void(*f)()) {

		if (m_pressed[keyid] == true) {
			(*f)();
		}
	}

	void Inputsystem::setKey(int ID, bool tof)		//trueorFalse
	{
		m_pressed[ID] = tof;
	}

}