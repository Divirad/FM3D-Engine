#include <Engine.h>
#include <chrono>
#include <iostream>

// Some Makros for the Window
#define	WIN_X 1600
#define	WIN_Y 900
#define WIN_CAP L"TestGame 3"

using ALL_FM3D_NAMESPACES;
using namespace FM3D::Math;

// ANIMATE MODEL-FUNCTION 
const AnimatedModel* GetModel(EntityPtr& e);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	#pragma region FM3D Engine Stuff

	#if DEBUG
	//
	// Start Console when DeBugging
	//
	Window::StartConsole();
	Output::Initialize();
	Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE);
	Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);
	#endif

	// Initializing the Filemanager
	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();
	
	// Initializing the rendersystem
	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);
	// Initialising the window
	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(WIN_X, WIN_Y, WIN_CAP);

	#if DEBUG
	//
	// Display Rendersystem error if something wents wrong in DebugMode
	//
	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	#else
	renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)
	#endif

	// Initializing the projectionmatrix
	Matrix4f projectionMatrix = Matrix4f::ProjectionFOV(70.0f, static_cast<float>(win->GetWidth()) / static_cast<float>(win->GetHeight()), 0.1f, 1000.0f);
	RenderTarget2D* target2D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer2D* renderer2D = renderSystem->CreateRenderer2D(target2D);
	RenderTarget2D* target3D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer3D* renderer3D = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight(), target3D);

	// Creating Camera
	Camera camera(Vector3f(0.0f, 5.0f, 0.0f));
	// ClearColor
	Color4f clearColor(0.0f, 0.0f, 0.0f, 1.0f);
	#pragma endregion
	
	// Entity-Collection
	EntityCollection scene;

	///#############################################
		//
		// Create Entities here
		//
	///#############################################

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) { 
			renderSystem->BeginRendering(clearColor);

		///#############################################
			//
			//	Submit objects here to renderer!
			//
		///#############################################

			renderer3D->Flush(camera.GetViewMatrix(), camera.GetPosition());
			

		///#############################################
			//
			// Enter Gamelogic here!
			//
			renderer3D->SetForceWireFrame(Inputsystem::GetInstance()->CheckKey(KEY_F5));
			camera.Preset(camera.FIRSTPERSON, false);
		///#############################################
		}
	};
	
	// Shutdown of the Rendersystem
	renderSystem->Shutdown();
	return 0;
}

// Camera-Move-Sample
void Move(Camera& camera) {
		Vector3f look = Math::GetLookingDirection2D(camera.GetRotation());
		Vector3f orthLook = Matrix4f::Rotation(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;

		bool forward = Inputsystem::GetInstance()->CheckKey(KEY_W);
		bool backward = Inputsystem::GetInstance()->CheckKey(KEY_S);
		bool left = Inputsystem::GetInstance()->CheckKey(KEY_A);
		bool right = Inputsystem::GetInstance()->CheckKey(KEY_D);

		float speedFW = 0.1f;
		float speedSW = 0.1f;
		if (Inputsystem::GetInstance()->CheckKey(KEY_STRG)) {
			speedFW = speedSW = 0.01f;
		}

		if (forward && !backward) {
			camera.GetPosition() += look * speedFW;
		}
		else if (!forward && backward) {
			camera.GetPosition() += look * -speedFW;
		}
		if (left && !right) {
			camera.GetPosition() += orthLook * speedSW;
		}
		else if (!left && right) {
			camera.GetPosition() += orthLook * -speedSW;
		}
		if (Inputsystem::GetInstance()->CheckKey(KEY_SPACE)) {
			camera.GetPosition().y += 0.1f;
		}
		if (Inputsystem::GetInstance()->CheckKey(0x10)) {
			camera.GetPosition().y -= 0.1f;
		}
}

// Animate Model
const AnimatedModel* GetModel(EntityPtr& e) {
	RenderableComponent* r = static_cast<RenderableComponent*>(e->GetComponent(RenderableComponentId));
	return static_cast<const AnimatedModel*>(r->GetModel());
}