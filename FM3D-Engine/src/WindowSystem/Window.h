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
		Input m_input;
	public:
		Window(const Window&) = delete;			//Prevent copying
		Window& operator= (const Window&) = delete;

		EventSource <SizeChangeEvent> &GetSizeChangeSource() { return m_winNewsize; }

		virtual bool Start(int width, int height, LPCWSTR title, bool fullscreen, bool showWindow = true);
		virtual bool ShouldClose() const = 0;
		virtual bool HasMessage() = 0;
		virtual void Close() = 0;

		static Window* Create(Platform p, HINSTANCE hInstance);
		static void StartConsole();
		static void SetConsolePosition(int x, int y);

		inline int GetWidth() { return m_width; }
		inline int GetHeight() { return m_height; }
		inline Vector2i GetWinSize(){ return  Vector2i(m_width,m_height); }

		virtual Vector2i GetWorkSize() = 0;
		virtual Vector2i GetWinPos() = 0;

		inline Input& GetInput() { return m_input; }
		inline const Input& GetInput() const { return m_input; }

		static inline Window* GetInstance() { return s_instance; }
		static inline Window* SetInstance(Window* win) { return s_instance = win; }
	};

}