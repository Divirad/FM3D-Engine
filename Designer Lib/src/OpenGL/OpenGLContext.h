#pragma once
#include "../pch.h"

namespace DesignerLib {

	class OpenGLContext {
	private:
		static WCHAR s_windowID;

		MSG m_msg;
		HWND m_hWnd;
		LPCWSTR m_name;
		HINSTANCE m_hInstance;

		HDC m_hDevContext;
		HGLRC m_hGLRenderContext;
	public:
		OpenGLContext(HINSTANCE hInst);
		bool Initialize();
	private:
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}