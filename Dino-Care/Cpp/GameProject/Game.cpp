#include "Game.h"

namespace Dino_Care {

	void Game::Initialize(HINSTANCE hInstance) {
		Output::Initialize();
		Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE);
		Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);

		FileManager::Initialize("res/", "../../../../FM3D-Engine/", "fm3d");
		ExternFileManager::Initialize();

		m_win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
	}

	void Game::Start() {
		m_win->Start(1600, 900, L"Dino-Care");
	}

	void Game::Loop() {
		LARGE_INTEGER time1;
		LARGE_INTEGER time2;
		LONGLONG t1;
		LONGLONG delta = 0LL;
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		while (!m_win->ShouldClose()) {
			if (!m_win->HasMessage()) {
				QueryPerformanceCounter(&time1);
				t1 = time1.QuadPart;
				t1 *= 1000000LL;
				t1 /= frequency.QuadPart;
				delta *= 1000000LL;
				delta /= frequency.QuadPart;
				Update(static_cast<double>(t1), static_cast<double>(delta));
				QueryPerformanceCounter(&time2);
				delta = time2.QuadPart - time1.QuadPart;
			}
		}
	}

	void Game::Update(double time, double timeDelta) {
	}

}