#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Window {
	public: 
		struct SizeChangeEvent { Vector2i winNewsize; Vector2i winOldsize; };

	private:
		static Window* s_instance;
	protected:
		Window();
		int m_width, m_height;
		EventSource <SizeChangeEvent> m_winNewsize;

		HWND m_hwnd;
	public:
		EventSource <SizeChangeEvent> &GetSizeChangeSource() { return m_winNewsize; }

		virtual bool Start(int width, int height, LPCWSTR title, bool showWindow = true);
		virtual bool ShouldClose() const = 0;
		virtual bool HasMessage() = 0;
		virtual void Close() = 0;

		static Window* Create(Platform p, HINSTANCE hInstance);
		static void StartConsole();
		static void SetConsolePosition(int x, int y);

		int GetWidth() { return m_width; }
		inline int GetHeight() { return m_height; }
		
		inline Vector2i GetWinSize(){ return  Vector2i(m_width,m_height); }
		inline Vector2i GetWorkSize() { return  Vector2i((int)GetSystemMetrics(SM_CXSCREEN), (int)GetSystemMetrics(SM_CYSCREEN)); }
		inline Vector2i GetWinPos() { 

			/*WINDOWPLACEMENT wp;
			HWND hw = *m_hwnd;
			GetWindowPlacement(hw, &wp);
*/	
			RECT rct;
			GetWindowRect(m_hwnd, &rct);
			std::cout<< Vector2i(rct.left, rct.top)<< std::endl;
			return Vector2i(rct.left, rct.top);
			//return Vector2i(wp.rcNormalPosition.left, wp.rcNormalPosition.top); 
		}

		inline HWND GetHWND() { return m_hwnd; };
		inline void SetHWND(HWND hwnd) { m_hwnd = hwnd; }

		static inline Window* GetInstance() { return s_instance; }
		static inline Window* SetInstance(Window* win) { return s_instance = win; }
	};

}