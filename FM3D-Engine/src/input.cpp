#include <Engine.h>

using namespace std;

namespace ENGINE_NAME
{
	Inputsystem Inputsystem::s_instance = Inputsystem();
	Inputsystem::Inputsystem()
	{
		m_mode = INSTANT;
	}
	Inputsystem::~Inputsystem()
	{

	}
	void Inputsystem::SetMouseMode(COORDS_MODE mode)
	{
		m_mode = mode;
	}

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
		switch (m_mode) {
		case CLICK:
			pressed[LorR] = true;
			lastpos.x = LOWORD(lParam);
			lastpos.y = HIWORD(lParam);
			cout << "\nINPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << lastpos.x << " AND Y: " << lastpos.y << "<< ACTIVATED\n";
			break;

		case RELEASE:
			pressed[LorR] = true;
			cout << "\nINPUT:: R  :: " << LorR << "-Mouse-Click ACTIVATED\n";
			break;

		case CLICK_RELEASE:
			pressed[LorR] = true;
			lastpos.x = LOWORD(lParam);
			lastpos.y = HIWORD(lParam);
			cout << "\nINPUT:: CR :: " << LorR << "-Mouse-Click @ the Coords >>X: " << lastpos.x << " AND Y: " << lastpos.y << "<< ACTIVATED\n";
			break;

		case INSTANT:
			pressed[LorR] = true;
			lastpos.x = LOWORD(lParam);
			lastpos.y = HIWORD(lParam);
			cout << "\nINPUT:: INS:: " << LorR << "-Mouse-Click @ the Coords >>X: " << lastpos.x << " AND Y: " << lastpos.y << "<< ACTIVATED\n";
			break;
		}

	}

	void Inputsystem::MReleased(LPARAM lParam, int LorR) {
		switch (m_mode) {
		case CLICK:
			pressed[LorR] = false;
			cout << "INPUT:: C  :: " << LorR << "-Mouse-Click  DEACTIVATED\n";
			break;

		case RELEASE:
			pressed[LorR] = false;
			cout << "INPUT:: C  :: " << LorR << "-Mouse-Click @ the Coords >>X: " << LOWORD(lParam) << " AND Y: " << HIWORD(lParam) << "<< DEACTIVATED\n";
			break;

		case CLICK_RELEASE:
			pressed[LorR] = false;
			cout << "INPUT:: CR :: " << LorR << "-Mouse-Click @ the Coords >>X: " << LOWORD(lParam) << " AND Y: " << HIWORD(lParam) << "<< DEACTIVATED\n";
			break;

		case INSTANT:
			pressed[LorR] = false;
			cout << "INPUT:: INS:: " << LorR << "-Mouse-Click @ the Coords >>X: " << LOWORD(lParam) << " AND Y: " << HIWORD(lParam) << "<< DEACTIVATED\n";
			break;
		}

	}

	void Inputsystem::MWheel(short wheeldata)
	{
		wheel = wheeldata;
		cout << "INPUT:: W  :: " << wheeldata << "-Wheeldata";
	}

	void Inputsystem::MMove(LPARAM lParam)
	{
		if (m_mode == INSTANT)
		{
			lastpos.x = LOWORD(lParam);
			lastpos.y = HIWORD(lParam);
			//cout << "INPUT:: INS:: Mouse @ the Coords >>X: " << LOWORD(lParam) << " AND Y: " << HIWORD(lParam) << "\n";
		}
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