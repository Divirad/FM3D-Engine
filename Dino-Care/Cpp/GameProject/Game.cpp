#include "Game.h"
#include "Logics.h"

namespace Dino_Care {

	Game::~Game() {
		delete m_renderer3D;
		delete m_renderer2D;
		delete m_target3D;
		delete m_target2D;
		delete m_renderSystem;

		delete m_renderLogic;
	}

	bool Game::Initialize(HINSTANCE hInstance) {
		Window::StartConsole();

		Output::Initialize();
		Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE);
		Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);

		FileManager::Initialize("res/", "../../../../FM3D-Engine/", "fm3d");
		ExternFileManager::Initialize();

		m_win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

		m_renderSystem = RenderSystem::Create(OpenGL3_3);
		if (!m_renderSystem->Initialize(m_win->GetWidth(),m_win->GetHeight(), false, ((Win32Window*)m_win)->GetHwnd(), false)) {
			std::cout << "Rendersystem Initializing Error!" << std::endl;
			return false;
		}

		m_target2D = m_renderSystem->CreateRenderTarget2D(Vector2i(m_win->GetWidth(), m_win->GetHeight()), true);
		m_renderer2D = m_renderSystem->CreateRenderer2D(m_target2D);
		m_target3D = m_renderSystem->CreateRenderTarget2D(Vector2i(m_win->GetWidth(), m_win->GetHeight()), true);
		Matrix4f projectionMatrix = Matrix4f::ProjectionFOV(70.0f, static_cast<float>(m_win->GetWidth()) / static_cast<float>(m_win->GetHeight()), 0.1f, 10000.0f);
		m_renderer3D = m_renderSystem->CreateRenderer3D(projectionMatrix, m_win->GetWidth(), m_win->GetHeight(), m_target3D);

		m_res.LoadResources(m_renderSystem);
		m_cres.Load(m_renderSystem);

		m_renderLogic = new RenderLogic(m_renderer3D, m_scene);

		auto allo = m_scene.CreateEntity();
		allo->Add<PositionComponent>(Vector3f(0.0f, 0.0f, 0.0f));
		allo->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
		allo->Add<ScaleComponent>(Vector3f(1.0f, 1.0f, 1.0f));
		Material alloMat(0xfffffff);
		Model* alloModel = new Model(m_res.GetMesh(MESH_ALLOSAURUS), std::vector<const Material*>{ &alloMat });
		allo->Add<RenderableComponent>(alloModel);
	}

	void Game::Start() {
		m_win->Start(1600, 900, L"Dino-Care", false);
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
		m_renderLogic->ExecuteForAll();
	}

}