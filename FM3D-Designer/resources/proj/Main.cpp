#define	WIN_X 1600
#define	WIN_Y 900
#define WIN_CAP L"TestGame 3"

#define SHADER_LIGHT "src/Graphics/OpenGL3.3/3D/Shader/Light.vert"
#define SHADER_GEOMETRY "src/Graphics/OpenGL3.3/3D/Shader/Geometry.vert"

#include <Engine.h>
#include <chrono>
#include <iostream>
#include "Resources.h"

using ALL_FM3D_NAMESPACES;
using namespace FM3D::Math;

// CREATE ENTITY-METHOD
EntityPtr CreateEntity(EntityCollection&, const Vector3f&, const Vector3f&, const Vector3f&, Model*);

// 
const AnimatedModel* GetModel(EntityPtr& e);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Window::StartConsole();

	Output::Initialize();
	Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE);
	Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);


	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();

	std::string vert = FileManager::ReadShaderFile(SHADER_LIGHT, {});
	std::string vert2 = FileManager::ReadShaderFile(SHADER_GEOMETRY, {});
	auto char0 = vert.back();
	auto char1 = vert2.back();
	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);
	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(WIN_X, WIN_Y, WIN_CAP);

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Matrix4f projectionMatrix = Matrix4f::ProjectionFOV(70.0f, static_cast<float>(win->GetWidth()) / static_cast<float>(win->GetHeight()), 0.1f, 1000.0f);
	RenderTarget2D* target2D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer2D* renderer2D = renderSystem->CreateRenderer2D(target2D);
	RenderTarget2D* target3D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer3D* renderer3D = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight(), target3D);

	EntityCollection scene;

	LARGE_INTEGER time1;
	LARGE_INTEGER time2;
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);


	Camera camera(Vector3f(0.0f, 5.0f, 0.0f));

	Color4f clearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Resources res(renderSystem);

	//
	// Create Entities here
	//

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) { 
			renderSystem->BeginRendering(clearColor);

			//
			//	START OF USER AREA
			//

				//
				//	Submit objects here!
				//

			//
			//	END OF USER AREA
			//

			Move(camera, laptopCam);
			renderer3D->SetForceWireFrame(Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_F5));
			renderer3D->Flush(camera.GetViewMatrix(), camera.GetPosition());
			camera.Preset(camera.FIRSTPERSON, false);

			//
			// Enter Gamelogic here!
			//

				//
				//	Submit objects here!
				//

			//
			//	END OF USER AREA
			//
		}
	};

	renderSystem->Shutdown();
	return 0;
}

void Move(Camera& camera, Camera& laptop) {

	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_LEFT)) {
		laptop.GetRotation().y += 3.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_RIGHT)) {
		laptop.GetRotation().y -= 3.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_UP)) {
		laptop.GetRotation().x += 3.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_DOWN)) {
		laptop.GetRotation().x -= 3.0f;
	}
	{
		Vector3f look = Math::GetLookingDirection2D(laptop.GetRotation());
		//std::cout << look << std::endl;
		Vector3f orthLook = Matrix4f::Rotation(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;

		bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_T);
		bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_G);
		bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_F);
		bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_H);

		float speedFW = 0.1f;
		float speedSW = 0.1f;
		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_STRG)) {
			speedFW = speedSW = 0.01f;
		}

		if (forward && !backward) {
			laptop.GetPosition() += look * speedFW;
		}
		else if (!forward && backward) {
			laptop.GetPosition() += look * -speedFW;
		}
		if (left && !right) {
			laptop.GetPosition() += orthLook * speedSW;
		}
		else if (!left && right) {
			laptop.GetPosition() += orthLook * -speedSW;
		}
		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_X)) {
			laptop.GetPosition().y += 0.1f;
		}
		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_Y)) {
			laptop.GetPosition().y -= 0.1f;
		}
	}

	{
		Vector3f look = Math::GetLookingDirection2D(camera.GetRotation());
		//std::cout << look << std::endl;
		Vector3f orthLook = Matrix4f::Rotation(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;

		bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_W);
		bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_S);
		bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_A);
		bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_D);

		float speedFW = 0.1f;
		float speedSW = 0.1f;
		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_STRG)) {
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
		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_SPACE)) {
			camera.GetPosition().y += 0.1f;
		}
		if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(0x10)) {
			camera.GetPosition().y -= 0.1f;
		}
	}
}

const AnimatedModel* GetModel(EntityPtr& e) {
	RenderableComponent* r = static_cast<RenderableComponent*>(e->GetComponent(RenderableComponentId));
	return static_cast<const AnimatedModel*>(r->GetModel());
}