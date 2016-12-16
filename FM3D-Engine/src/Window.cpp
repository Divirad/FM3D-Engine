#include <Engine.h>

namespace FM3D {

	Window* Window::s_instance = nullptr;

	Window::Window() {
		
	}

	Window* Window::Create(Platform p, HINSTANCE hInstance) {
		switch (p) {
		case WINDOWS:
			return new Win32Window(hInstance);
		default:
			return nullptr;
		}
	}

	void Window::SetConsolePosition(int x, int y) {
		COORD pos = { (short)x, (short)y };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
	}

	void Window::StartConsole() {
		AllocConsole();
		FILE* pCout;
		freopen_s(&pCout, "CONOUT$", "w", stdout);
		std::cout << "Console started!" << std::endl;
	}

	bool Window::Start(int width, int height, LPCWSTR title) {
		m_width = width;
		m_height = height;
		return true;
	}
}