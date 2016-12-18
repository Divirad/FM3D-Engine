#include "OpenGLContext.h"

namespace DesignerLib {

	WCHAR OpenGLContext::s_windowID = 1;

	OpenGLContext::OpenGLContext(HINSTANCE hInst) : m_msg({ 0 }), m_hWnd(nullptr), m_name(nullptr), m_hInstance(hInst) {
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
		m_name = L"EngineMainWindow", s_windowID++;
		wcex.lpszClassName = m_name;
		wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
		if (!RegisterClassEx(&wcex)) {
			std::cerr << "Error on Registering WNDCLASSEX" << std::endl;
			MessageBox(NULL, L"Error on Registering WNDCLASSEX", L"Error in DesignerLib", MB_OK);
		}
	}

	bool OpenGLContext::Initialize() {
		RECT rc = { 0, 0, 1, 1 };
		DWORD windowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX);
		AdjustWindowRect(&rc, windowStyle, 0);
		m_hWnd = CreateWindow(m_name, NULL, windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
		if (!m_hWnd) {
			std::cerr << "Error on Creating Window" << std::endl;
			MessageBox(NULL, L"Error on Creating Window", L"Error in DesignerLib", MB_OK);
			return false;
		}

		m_hDevContext = GetDC(m_hWnd);

		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		int format = ChoosePixelFormat(m_hDevContext, &pfd);
		if (!SetPixelFormat(m_hDevContext, format, &pfd))
			throw std::exception();

		m_hGLRenderContext = wglCreateContext(m_hDevContext);
		if (!wglMakeCurrent(m_hDevContext, m_hGLRenderContext))
			throw std::exception();

		if (glewInit())
			throw std::exception();

		typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
		PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

		const char *extensions = (char*)glGetString(GL_EXTENSIONS);

		return true;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		};
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}