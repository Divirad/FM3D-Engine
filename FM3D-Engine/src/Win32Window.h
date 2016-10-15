#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Win32Window : public Window {
	private:
		static WCHAR s_maxWindowID;

		MSG m_msg;
		HWND m_hWnd;
		LPCWSTR m_name;
		HINSTANCE m_hInstance;

		Win32Window(HINSTANCE hInstance);
	public:
		bool Start(int width, int height, LPCWSTR title) override;
		bool ShouldClose() const override;
		bool HasMessage();
		void Close() override;

		inline HWND GetHwnd() { return m_hWnd; }
	private:
		
		friend LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		friend Window;
	};

}