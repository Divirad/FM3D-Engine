#include <Engine.h>

using namespace std;

namespace ENGINE_NAME
{
	Inputsystem Inputsystem::s_instance = Inputsystem();
	Inputsystem::Inputsystem(){}
	Inputsystem::~Inputsystem(){}

	void Inputsystem::keyPressed(WPARAM wParam) {

		if (pressed[wParam] != true)
		{
			pressed[wParam] = true;
			cout << "INPUT:: K  :: >>" << wParam << "<< ACTIVATED\n";
		}
	}
	void Inputsystem::keyReleased(WPARAM wParam) {
		pressed[wParam] = false;
		cout << "INPUT:: K  :: >>" << wParam << "<< DEACTIVATED\n";
	}

	void Inputsystem::MPressed(LPARAM lParam, int LorR) {
		pressed[LorR] = true;
		lastposclick.x = LOWORD(lParam);
		lastposclick.y = HIWORD(lParam);
		cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << lastposclick.x << " AND Y: " << lastposclick.y << "<< ACTIVATED\n";
	}

	void Inputsystem::MReleased(LPARAM lParam, int LorR) {
		pressed[LorR] = true;
		lastposclick.x = LOWORD(lParam);
		lastposclick.y = HIWORD(lParam);
		cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << lastposclick.x << " AND Y: " << lastposclick.y << "<< ACTIVATED\n";
	}

	void Inputsystem::MWheel(short wheeldata)
	{
		wheel = wheeldata;
		cout << "INPUT:: W  :: " << wheeldata << "-Wheeldata";
	}

	void Inputsystem::MMove(LPARAM lParam)
	{/*
		if (m_mode == INSTANT)
		{*/
			lastposinst.x = LOWORD(lParam);
			lastposinst.y = HIWORD(lParam);
			cout << "INPUT:: INS:: Mouse @ the Coords >>X: " << LOWORD(lParam) << " AND Y: " << HIWORD(lParam) << "\n";
		//}
	}

	bool Inputsystem::CheckIfKeyIsPressed(int keyid)
	{
		if (pressed[keyid] == true)
		{
			return  true;
		}
		else { return false; }
	}

	void Inputsystem::DoIfKeyPressed(int keyid, void(*f)()) {

		if (pressed[keyid] == true) {
			(*f)();
		}
	}

	void Inputsystem::setKey(int ID, bool tof)		//trueorFalse
	{
		pressed[ID] = tof;
	}

}