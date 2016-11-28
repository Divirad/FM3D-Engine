#include <Engine.h>

namespace FM3D {

	WCHAR Win32Window::s_maxWindowID = 1;

	Win32Window::Win32Window(HINSTANCE hInstance) : m_msg({ 0 }), m_hWnd(nullptr), m_name(nullptr), m_hInstance(hInstance) {
		/*/HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
		if (FAILED(hr)) {
		std::cout << "Error on CoInitializeEx()" << std::endl;
		return false;
		}*/

		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInstance;
		wcex.hIcon = LoadIcon(m_hInstance, L"IDI_ICON");
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		m_name = L"EngineMainWindow", s_maxWindowID++;
		wcex.lpszClassName = m_name;
		wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
		if (!RegisterClassEx(&wcex)) {
			std::cout << "Error on Registering WNDCLASSEX" << std::endl;
		}
	}

	bool Win32Window::Start(int width, int height, LPCWSTR title) {
		Window::Start(width, height, title);
		RECT rc = { 0, 0, width, height };
		DWORD windowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX );
		AdjustWindowRect(&rc, windowStyle, 0);
		m_hWnd = CreateWindow(m_name, title, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
		if (!m_hWnd) {
			std::cout << "Error on Creating Window" << std::endl;
			return false;
		}

		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		return true;
	}

	bool Win32Window::ShouldClose() const {
		return WM_QUIT == m_msg.message;
	}

	bool Win32Window::HasMessage() {
		if (PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
			return true;
		} else {
			return false;
		}
	}

	void Win32Window::Close() {
		DestroyWindow(m_hWnd);
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		
		Inputsystem* InputWP = Inputsystem::GetInstance();
		
		Window *win = Window::GetInstance();

		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			InputWP->keyPressed(wParam);
			break; 
		case WM_KEYUP:
			InputWP->keyReleased(wParam);
			break;
		case WM_LBUTTONDOWN:
			InputWP->MPressed(lParam, MOUSE_LEFT);
			break;
		case WM_RBUTTONDOWN:
			InputWP->MPressed(lParam, MOUSE_RIGHT);
			break;
		case WM_LBUTTONUP:
			InputWP->MReleased(lParam, MOUSE_LEFT);
			break;
		case WM_RBUTTONUP:
			InputWP->MReleased(lParam, MOUSE_RIGHT);
			break;
		case WM_MOUSEHWHEEL:
			InputWP->MWheel(GET_WHEEL_DELTA_WPARAM(wParam));		//DOESNT WURK!
			break;
		case WM_MOUSEMOVE:
			InputWP->MMove(lParam);
			break;
		case WM_SIZE:
			Window::SizeChangeEvent scevent = { Vector2i(LOWORD(lParam), HIWORD(lParam)), Vector2i(win->GetWidth(), win->GetHeight()) };
			win->GetSizeChangeSource().FireEvent(&scevent);
			((Win32Window*)win)->m_height = HIWORD(lParam);
			((Win32Window*)win)->m_width = LOWORD(lParam);
			break;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}