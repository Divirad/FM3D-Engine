#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Win32Window : public Window {
	private:
		static WCHAR s_maxWindowID;

		MSG m_msg;
		HWND m_hWnd;
		std::wstring m_name;
		HINSTANCE m_hInstance;

		Win32Window(HINSTANCE hInstance);
	public:
		bool Start(int width, int height, LPCWSTR title, bool fullscreen, bool showWindow = true) override;
		bool ShouldClose() const override;
		bool HasMessage();
		void Close() override;

		Vector2i GetWorkSize() override;
		Vector2i GetWinPos() override;

		inline HWND GetHwnd() { return m_hWnd; }
	private:
		
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		friend Window;
	};

}