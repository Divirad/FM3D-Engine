#include <Engine.h>
#include <chrono>
#include <iomanip>

using namespace Engine;

void Move(Camera& camera);


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();

	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(1280, 720, L"TestGame 3");

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)win->GetWidth() / (float)win->GetHeight(), 0.1f, 1000.0f);

	RenderTarget2D* target2D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer2D* renderer2D = renderSystem->CreateRenderer2D(target2D);
	//Renderer3D* renderer3D = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight());

	LARGE_INTEGER time1;
	LARGE_INTEGER time2;

	Camera camera;

	Color4f clearColor(1.0f, 0.5f, 0.2f, 1.0f);

	Engine::Font* font;
	ExternFileManager::ReadFontFile("font.ttf", 50, Vector2f(0.001f, 0.001f), renderSystem->CreateTexture(), &font);

	Texture* emptyTex = renderSystem->CreateTexture();
	float pixels[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	emptyTex->Initialize(2, 2, Texture::NEAREST, Texture::CLAMP, pixels, 32);

	Text text0{ "Hallo", font, 0xff000000 };
	Text text1{ "Tschau", font, 0xff000000 };
	Quad textBack(Vector3f(-1.0f, 0.3f, 0.0f), Vector2f(0.2f, 0.3f), 0xfffff00f, emptyTex);

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			QueryPerformanceCounter(&time1);

			renderSystem->BeginRendering(clearColor);

			//renderer3D->Flush(camera.GetViewMatrix(), camera.GetPosition());

			renderer2D->Begin();
			renderer2D->Submit(&textBack);
			renderer2D->DrawString(text0, Vector3f(-0.975f, 0.5f, 0.0f));
			renderer2D->DrawString(text1, Vector3f(-0.975f, 0.4f, 0.0f));
			renderer2D->End();
			renderer2D->Flush();

			renderSystem->EndRendering();

			QueryPerformanceCounter(&time2);
			LONGLONG time = time2.QuadPart - time1.QuadPart;
			text0.txt = std::to_string(1.0f / (float)time);
			text1.txt = std::to_string(time);
		}
	};

	renderSystem->Shutdown();
}

void Move(Camera& camera) {
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_LEFT)) {
		camera.GetRotation().y += 1.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_RIGHT)) {
		camera.GetRotation().y -= 1.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_UP)) {
		camera.GetRotation().x += 1.0f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_DOWN)) {
		camera.GetRotation().x -= 1.0f;
	}



	Vector3f look = Math::GetLookingDirection2D(camera.GetRotation());
	Vector3f orthLook = Matrix4f::Rotate(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;

	bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_W);
	bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_S);
	bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_A);
	bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_D);

	float speedFW = 0.1f;
	float speedSW = 0.1f;

	if (forward && !backward) {
		camera.GetPosition() += speedFW * look;
	} else if (!forward && backward) {
		camera.GetPosition() += -speedFW * look;
	}
	if (left && !right) {
		camera.GetPosition() += speedSW * orthLook;
	} else if (!left && right) {
		camera.GetPosition() += -speedSW * orthLook;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_SPACE)) {
		camera.GetPosition().y += 0.1f;
	}
	if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(0x10)) {
		camera.GetPosition().y -= 0.1f;
	}

}

