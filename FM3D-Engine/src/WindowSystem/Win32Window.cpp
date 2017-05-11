#include <Engine.h>

namespace FM3D {

	WCHAR Win32Window::s_maxWindowID = 1;

	Win32Window::Win32Window(HINSTANCE hInstance) : m_msg({ 0 }), m_hWnd(nullptr), m_name(), m_hInstance(hInstance) {
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
		m_name = (L"EngineMainWindow" + std::to_wstring(s_maxWindowID++));
		wcex.lpszClassName = m_name.c_str();
		wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
		if (!RegisterClassEx(&wcex)) {
			std::cout << "Error on Registering WNDCLASSEX" << std::endl;
		}
	}

	bool Win32Window::Start(int width, int height, LPCWSTR title, bool fullscreen, bool showWindow) {
		Window::Start(width, height, title, fullscreen, showWindow);
		RECT rc = { 0, 0, width, height };

		if (fullscreen)                                             // Attempt Fullscreen Mode?
		{
			DEVMODE dmScreenSettings;                               // Device Mode
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));   // Makes Sure Memory's Cleared
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);       // Size Of The Devmode Structure
			dmScreenSettings.dmPelsWidth = width;                // Selected Screen Width
			dmScreenSettings.dmPelsHeight = height;               // Selected Screen Height
			dmScreenSettings.dmBitsPerPel = 32;                 // Selected Bits Per Pixel
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
			if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
				std::cerr << "Error on changing Display Settings" << std::endl;
				return false;
			}

			DWORD windowStyle = (WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
			AdjustWindowRectEx(&rc, windowStyle, 0, WS_EX_APPWINDOW);
			m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_name.c_str(), title, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
		}
		else {
			DWORD windowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX);
			AdjustWindowRect(&rc, windowStyle, 0);
			m_hWnd = CreateWindow(m_name.c_str(), title, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
		}
		if (!m_hWnd) {
			std::cout << "Error on Creating Window" << std::endl;
			return false;
		}
		SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
		if(showWindow) ShowWindow(m_hWnd, SW_SHOWDEFAULT);
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

	Vector2i Win32Window::GetWorkSize() {
		return  Vector2i((int)GetSystemMetrics(SM_CXSCREEN), (int)GetSystemMetrics(SM_CYSCREEN));
	}

	Vector2i Win32Window::GetWinPos() {
		RECT rct;
		GetWindowRect(m_hWnd, &rct);
		return Vector2i(rct.left, rct.top);
	}

	LRESULT CALLBACK Win32Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		
		Window* win = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (win) {
			Input& inp = win->GetInput();

			switch (message) {
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
				inp.KeyPressed(wParam);
				break;
			case WM_KEYUP:
				inp.KeyReleased(wParam);
				break;
			case WM_LBUTTONDOWN:
				inp.MPressed(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)), MOUSE_LEFT);
				break;
			case WM_RBUTTONDOWN:
				inp.MPressed(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)), MOUSE_RIGHT);
				break;
			case WM_LBUTTONUP:
				inp.MReleased(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)), MOUSE_LEFT);
				break;
			case WM_RBUTTONUP:
				inp.MReleased(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)), MOUSE_RIGHT);
				break;
			case WM_MOUSEHWHEEL:
				inp.MWheel(GET_WHEEL_DELTA_WPARAM(wParam));		//DOESNT WURK!
				break;
			case WM_MOUSEMOVE:
				inp.MMove(static_cast<float>(GET_X_LPARAM(lParam)), static_cast<float>(GET_Y_LPARAM(lParam)));
				//std::cout << "Move " << GET_X_LPARAM(lParam) << "  " << GET_Y_LPARAM(lParam) << std::endl;
				break;
			case WM_SIZE:
				Window::SizeChangeEvent scevent = { Vector2i(LOWORD(lParam), HIWORD(lParam)), Vector2i(win->GetWidth(), win->GetHeight()) };
				win->GetSizeChangeSource().FireEvent(&scevent);
				((Win32Window*)win)->m_height = HIWORD(lParam);
				((Win32Window*)win)->m_width = LOWORD(lParam);
				break;
			}
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}