#include <Engine.h>
#include <chrono>
#include <iomanip>

using namespace Engine;

void TestButton(HINSTANCE hInstance);
void StarwarsScene(HINSTANCE hInstance);


///////////////////////////////////////////////////////////////
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	TestButton(hInstance);
}
///////////////////////////////////////////////////////////////



void StarwarsScene(HINSTANCE hInstance) {
	Window::StartConsole();
	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();

	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(1280, 720, L"JOOONGE");

	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)win->GetWidth() / (float)win->GetHeight(), 0.1f, 1000.0f);

	//projectionMatrix.Transpose();
	Renderer3D* renderer = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight());

	Texture* emptyTex = renderSystem->CreateTexture(NULL);
	float pixels[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	emptyTex->Initialize(2, 2, Texture::NEAREST, Texture::CLAMP, pixels, 32);

	//Texture* trooperTex = renderSystem->CreateTexture(NULL);
	//ExternFileManager::ReadTextureFile("Stormtrooper_d.tga", trooperTex, Texture::NEAREST);
	//Texture* blasterTex = renderSystem->CreateTexture(NULL);
	//ExternFileManager::ReadTextureFile("E11_Blaster_d.tga", blasterTex, Texture::NEAREST);

	//Model* trooperMesh;
	//ExternFileManager::ReadModelFile("Stormtrooper.dae", renderSystem, &trooperMesh, false, false);

	//Array<const Material*>& materials = trooperMesh->GetMaterials();
	//Material mat1 = { 0xffffffff, blasterTex };
	//Material mat2 = { 0xffffffff, blasterTex };
	//Material mat3 = { 0xffffffff, trooperTex };

	//materials[0] = &mat1;
	//materials[1] = &mat2;
	//materials[2] = &mat3;

	//Entity trooper1(Vector3f(-2.0f, -2.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), trooperMesh);
	//Entity trooper2(Vector3f(2.0f, -2.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), trooperMesh);
	
	Texture* bobaTexBody = renderSystem->CreateTexture(NULL);
	ExternFileManager::ReadTextureFile("Fett_body_D.tga", bobaTexBody, Texture::NEAREST);
	Texture* bobaTexJet = renderSystem->CreateTexture(NULL);
	ExternFileManager::ReadTextureFile("Fett_jetpak_D.tga", bobaTexJet, Texture::NEAREST);
	Texture* bobaTexHelmet = renderSystem->CreateTexture(NULL);
	ExternFileManager::ReadTextureFile("Fett_helmet_D.tga", bobaTexHelmet, Texture::NEAREST);
	Texture* bobaTexDisplay = renderSystem->CreateTexture(NULL);
	ExternFileManager::ReadTextureFile("Fett_display_D.tga", bobaTexDisplay, Texture::NEAREST);

	Model* bobaMesh;
	ExternFileManager::ReadModelFile("bobaFett.dae", renderSystem, &bobaMesh, false, true);

	Array<const Material*>& materialsBoba = bobaMesh->GetMaterials();
	Material mat1Boba = { 0xffffffff, bobaTexJet };
	Material mat2Boba = { 0xffffffff, bobaTexDisplay };
	Material mat3Boba = { 0xffffffff, bobaTexHelmet };
	Material mat4Boba = { 0xffffffff, bobaTexJet };
	Material mat5Boba = { 0xffffffff, bobaTexBody };

	materialsBoba[0] = &mat1Boba;
	materialsBoba[1] = &mat2Boba;
	materialsBoba[2] = &mat3Boba;
	materialsBoba[3] = &mat4Boba;
	materialsBoba[4] = &mat5Boba;

	Entity boba(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(180.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), bobaMesh);
	boba.GetAnimations().push_back({ 0u, 0.0 });

	float color[4] = { 0.2f, 0.5f, 0.5f, 1.0f };

	Camera camera(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f));

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {

			renderSystem->BeginRendering(color);

			//renderer->Submit(&trooper1);
			//renderer->Submit(&trooper2);
			renderer->Submit(&boba);
			renderer->Flush(camera.GetViewMatrix(),camera.GetPosition());

			renderSystem->EndRendering();
			boba.GetAnimations()[0].time += 1.0 / 60.0;

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
			//std::cout << std::endl << look;
			Vector3f orthLook = Matrix4f::Rotate(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;

			bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_W);
			bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_S);
			bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_A);
			bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_D);

			float speedFW = 0.1f;
			float speedSW = 0.1f;

			if(forward && !backward) {
				camera.GetPosition() += speedFW * look;
			} else if(!forward && backward) {
				camera.GetPosition() += -speedFW * look;
			}
			if(left && !right) {
				camera.GetPosition() += speedSW * orthLook;
			} else if(!left && right) {
				camera.GetPosition() += -speedSW * orthLook;
			}
			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_SPACE)) {
				camera.GetPosition().y += 0.1f;
			}
			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(0x10)) {
				camera.GetPosition().y -= 0.1f;
			}

			
		}
	};

	renderSystem->Shutdown();
}




void TestButton(HINSTANCE hInstance) {
	Window::StartConsole();
	FileManager::Initialize("res/", "", "fm3d");
	ExternFileManager::Initialize();
	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
	win->Start(1280, 720, L"JOOONGE");
	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), false, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Renderer2D* renderer = renderSystem->CreateRenderer2D();	Matrix4f projectionMatrix = Matrix4f::Identity();
	renderer->Initialize(projectionMatrix);	Texture* Test_Tex = renderSystem->CreateTexture(NULL);	ExternFileManager::ReadTextureFile("knoebsche100x50.jpg", Test_Tex, Texture::NEAREST);	CompCoords::Initialize(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());	//Button MyFirstButton(Test_Tex, Vector2f(0.0f, 0.0f));

	Button MyFirstButton(0xffffffff, Test_Tex, Vector3f(0.1f, -1.0f, 0.0f), Vector2f(CompCoords::PixelToScreenSpace(Vector2f(100.0f, 50.0f))));
	
	//MyFirstButton.AutoSize();
	Engine::Font* f;
	ExternFileManager::ReadFontFile("fontilein.ttf", 20, Vector2f(0.001f, 0.001f), renderSystem->CreateTexture(""), &f);
	unsigned long long times[100];
	uint counter = 0;
	uint waiting = 30000;
	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			//VOLL DIE SCHLEIFE UND SOO
			renderSystem->BeginRendering(new float[4]{ 0.2f, 0.5f, 0.5f, 1.0f });
			renderer->Begin();
			renderer->Submit(&MyFirstButton);
			if (MyFirstButton.Click(MOUSE_LEFT))
			{
				//MessageBox(NULL, L"IT WOAAAKS!!!", NULL, NULL);
				Inputsystem::GetInstance()->SetMouseOption(Inputsystem::CLICK_RELEASE);
				
				/*MyFirstButton.HCenter();
				MyFirstButton.AutoSize();*/
				//MyFirstButton.HCenter();
				MyFirstButton.AutoSize();
			}
			renderer->End();
			renderer->Flush();
			renderSystem->EndRendering();
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		}
	};
	renderSystem->Shutdown();
}

