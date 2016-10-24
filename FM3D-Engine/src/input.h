#pragma once
#include <Engine.h>

#pragma warning(push)
#pragma warning(disable:4005)

//KEYCODES
//VollDieKrasseÄnderung 2.0
#define MOUSE_LEFT		1
#define MOUSE_RIGHT		2
#define KEY_RIGHT		3
#define MOUSE_MIDDLE	4

#define KEY_BACKSPACE	8
#define KEY_CAPSLOCK	9

#define KEY_CLEAR		12
#define KEY_ENTER		13
#define KEY_SHIFT		16
#define KEY_STRG		17
#define KEY_MENU		18
#define KEY_PAUSE		19

#define KEY_ESC			27

#define KEY_SPACE		32
#define KEY_LEFT		37
#define KEY_UP			38
#define KEY_RIGHT		39
#define KEY_DOWN		40
#define KEY_SELECT		41
#define	KEY_PRINT		42
#define KEY_EXECUTE		43
#define KEY_SNAPSHOT	44
#define KEY_INS			45

#define KEY_HELP		47

//Key0 Through Key9 Are the Same as Their ASCII Equivalents: '0' Through '9
#define KEY_1 48
#define KEY_2 49
#define KEY_3 50
#define KEY_4 51
#define KEY_5 52
#define KEY_6 53
#define KEY_7 54
#define KEY_8 55
#define KEY_9 56
#define KEY_0 57


//KeyA Through KeyZ Are the Same as Their ASCII Equivalents: 'A' Through 'Z'
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86 
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90

#define KEY_WIN_HOME		91
#define KEY_WIN_MENU		93


//Keys on the Numeric Keypad
#define KEY_NP1			96
#define KEY_NP2			97
#define KEY_NP3			98
#define KEY_NP4			99
#define KEY_NP5			100
#define KEY_NP6			101
#define KEY_NP7			102
#define KEY_NP8			103
#define KEY_NP9			104
#define KEY_NP0			105
#define KEY_NPMULTY		106
#define KEY_NPADD		107
#define KEY_NPSEP		108
#define KEY_NPSUB		109
#define KEY_NPDEC		110
#define KEY_NPDIV		111

//FUNCTION KEYS
#define KEY_F1			112
#define KEY_F2			113
#define KEY_F3			114
#define KEY_F4			115
#define KEY_F5			116
#define KEY_F6			117
#define KEY_F7			118
#define KEY_F8			119
#define KEY_F9			120

#pragma warning(pop)

namespace ENGINE_NAME 
{
	class ENGINE_DLL Inputsystem
	{
	public:
		//Enum for Mousetracking system
		enum COORDS_MODE{
			CNULL,
			CLICK,
			RELEASE,
			CLICK_RELEASE,
			INSTANT
		};

	private:
		//Static Object
		static Inputsystem s_instance;
		//Array for Key-Checking (using the makros from above) 
		//Each Array field has the same Char-ID like the keys
		//Except the Mouse
		bool pressed[121]{ 0 };
		//Mode for Mousetracking
		COORDS_MODE m_mode;
		//Vector for tracking the last position of mouse
		Vector2f lastposclick;
		Vector2f lastposinst;

		short wheel;		

	public:
		static Inputsystem* GetInstance() { return &s_instance; }
		Inputsystem();
		~Inputsystem();

		void Initialise(){}

		#pragma region Keys
		void keyPressed(WPARAM wParam);
		void keyReleased(WPARAM wParam);
		void setKey(int ID, bool tof);
		#pragma endregion

		#pragma region	Mouse
		void MPressed(LPARAM lParam, int LorR);
		void MReleased(LPARAM lParam, int LorR);
		void MMove(LPARAM lParam);

		void MWheel(short wheeldata);				//doesn't work!!
		#pragma endregion

		#pragma region Options
		//void SetWindow(Window*window) { win = window; }	//Gibt komischen Fehler
		void SetMouseMode(COORDS_MODE mode);
		#pragma endregion

		Vector2f GetLastposClick() { return lastposclick; }
		Vector2f GetLastposInst() { return lastposinst; }

		void DoIfKeyPressed(int keyid, void(*f)());
		bool CheckIfKeyIsPressed(int keyid);

	};

}