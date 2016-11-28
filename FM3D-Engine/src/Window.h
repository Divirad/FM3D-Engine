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
	public:
		EventSource <SizeChangeEvent> &GetSizeChangeSource() { return m_winNewsize; }

		virtual bool Start(int width, int height, LPCWSTR title);
		virtual bool ShouldClose() const = 0;
		virtual bool HasMessage() = 0;
		virtual void Close() = 0;

		static Window* Create(Platform p, HINSTANCE hInstance);
		static void StartConsole();
		static void SetConsolePosition(int x, int y);

		int GetWidth() { return m_width; }
		inline int GetHeight() { return m_height; }

		static inline Window* GetInstance() { return s_instance; }
		static inline Window* SetInstance(Window* win) { return s_instance = win; }
	};

}