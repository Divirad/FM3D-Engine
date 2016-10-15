#include <Engine.h>
#include <chrono>
#include <iomanip>

using namespace Engine;

void FPS2D(HINSTANCE hInstance);
void StarwarsScene(HINSTANCE hInstance);


///////////////////////////////////////////////////////////////
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	FPS2D(hInstance);
}
///////////////////////////////////////////////////////////////



//void StarwarsScene(HINSTANCE hInstance) {
//	Window::StartConsole();
//	FileManager::Initialize("res/", "", "fm3d");
//	ExternFileManager::Initialize();
//
//	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
//
//	win->Start(1280, 720, L"JOOONGE");
//
//	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);
//
//	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
//		std::cout << "Rendersystem Initializing Error!" << std::endl;
//	}
//	Renderer3D* renderer = renderSystem->CreateRenderer3D();
//	
//	Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, 1280 / 720, 0.1f, 1000.0f);
//	
//	projectionMatrix.Transpose();
//	renderer->Initialize(projectionMatrix);
//
//	Texture* emptyTex = renderSystem->CreateTexture(NULL);
//	float pixels[] = {
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f
//	};
//	emptyTex->Initialize(2, 2, Texture::NEAREST, Texture::CLAMP, pixels, 32);
//
//	Texture* trooperTex = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Stormtrooper_d.tga", trooperTex, Texture::NEAREST);
//	Texture* blasterTex = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("E11_Blaster_d.tga", blasterTex, Texture::NEAREST);
//
//	Mesh* trooperMesh;
//	ExternFileManager::ReadMeshFile("Stormtrooper.dae", renderSystem, &trooperMesh);
//
//	std::vector<Material*> materials(trooperMesh->GetNeededMaterialCount());
//	Material mat1 = { 0xffffffff, blasterTex };
//	Material mat2 = { 0xffffffff, blasterTex };
//	Material mat3 = { 0xffffffff, trooperTex };
//
//	materials[0] = &mat1;
//	materials[1] = &mat2;
//	materials[2] = &mat3;
//
//	Entity trooper1(Vector3f(-2.0f, -2.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), trooperMesh, materials);
//	Entity trooper2(Vector3f(2.0f, -2.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), trooperMesh, materials);
//	
//	Texture* bobaTexBody = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_body_D.tga", bobaTexBody, Texture::NEAREST);
//	Texture* bobaTexJet = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_jetpak_D.tga", bobaTexJet, Texture::NEAREST);
//	Texture* bobaTexHelmet = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_helmet_D.tga", bobaTexHelmet, Texture::NEAREST);
//	Texture* bobaTexDisplay = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_display_D.tga", bobaTexDisplay, Texture::NEAREST);
//
//	Mesh* bobaMesh;
//	ExternFileManager::ReadMeshFile("bobaFett.dae", renderSystem, &bobaMesh);
//
//	std::vector<Material*> materialsBoba(bobaMesh->GetNeededMaterialCount());
//	Material mat1Boba = { 0xffffffff, bobaTexJet };
//	Material mat2Boba = { 0xffffffff, bobaTexDisplay };
//	Material mat3Boba = { 0xffffffff, bobaTexHelmet };
//	Material mat4Boba = { 0xffffffff, bobaTexJet };
//	Material mat5Boba = { 0xffffffff, bobaTexBody };
//
//	materialsBoba[0] = &mat1Boba;
//	materialsBoba[1] = &mat2Boba;
//	materialsBoba[2] = &mat3Boba;
//	materialsBoba[3] = &mat4Boba;
//	materialsBoba[4] = &mat5Boba;
//
//	Entity boba(Vector3f(0.0f, -2.0f, -3.0f), Vector3f(180.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), bobaMesh, materialsBoba);
//	boba.GetAnimations().push_back({ 0u, 0.0 });
//
//	float color[4] = { 0.2f, 0.5f, 0.5f, 1.0f };
//
//	Camera camera(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f));
//
//	while (!win->ShouldClose()) {
//		if (!win->HasMessage()) {
//			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//
//			renderSystem->BeginRendering(color);
//
//			renderer->Submit(&trooper1);
//			renderer->Submit(&trooper2);
//			renderer->Submit(&boba);
//			renderer->Flush(camera.GetViewMatrix());
//
//			renderSystem->EndRendering();
//			boba.GetAnimations()[0].time += 1.0 / 60.0;
//			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
//			Window::SetConsolePosition(0, 1);
//			long long fps = 1000000 / duration;
//			std::cout << std::setw(7) <<  fps << "   ";
//
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_LEFT)) {
//				camera.GetRotation().y += 1.0f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_RIGHT)) {
//				camera.GetRotation().y -= 1.0f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_UP)) {
//				camera.GetRotation().x += 1.0f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_DOWN)) {
//				camera.GetRotation().x -= 1.0f;
//			}
//
//			
//
//			Vector3f look = Math::GetLookingDirection2D(camera.GetRotation());
//			std::cout << std::endl << look;
//			Vector3f orthLook = Matrix4f::Rotate(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;
//
//			bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_W);
//			bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_S);
//			bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_A);
//			bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_D);
//
//			float speedFW = 0.1f;
//			float speedSW = 0.1f;
//
//			if(forward && !backward) {
//				camera.GetPosition() += speedFW * look;
//			} else if(!forward && backward) {
//				camera.GetPosition() += -speedFW * look;
//			}
//			if(left && !right) {
//				camera.GetPosition() += speedSW * orthLook;
//			} else if(!left && right) {
//				camera.GetPosition() += -speedSW * orthLook;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_SPACE)) {
//				camera.GetPosition().y += 0.1f;
//			}
//			/*if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(0x10)) {
//				camera.GetPosition().y -= 0.1f;
//			}*/
//
//			
//		}
//	};
//
//	renderSystem->Shutdown();
//}

void FPS2D(HINSTANCE hInstance) {
	Window::StartConsole();

	
	FileManager::Initialize("res/", "", "fm3d");
	ExternFileManager::Initialize();

	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
		win->Start(1280, 720, L"JOOONGE");
		Inputsystem::GetInstance()->SetWindow(win);
		//Inputsystem::GetInstance()->SetMouseOption(Inputsystem::INSTANT);
	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), false, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Renderer2D* renderer = renderSystem->CreateRenderer2D();

	Matrix4f projectionMatrix = Matrix4f::Identity();
	
	
	renderer->Initialize(projectionMatrix);

	Texture* tex = renderSystem->CreateTexture(NULL);
	float* pixels = new float[4 * 6]{
		1.0f, 0.0f, 0.0f, 1.0f,	
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f
	};
	tex->Initialize(3, 2, Texture::NEAREST, Texture::CLAMP, pixels, 32);

	

	float r = 0x0, g = 0x0, b = 0x0, time = 0x0;
	bool br = false, bg = false, bb = false;
	Quad q(Vector3f(0.0f, 0.0f, 0.0f), Vector2f(0.5, 0.5f), 0xffffffff, tex);


	////////////////////////////////////////////////////////////////////
	
	Texture* Test_Tex = renderSystem->CreateTexture(NULL);
	ExternFileManager::ReadTextureFile("knoebsche100x50.jpg", Test_Tex, Texture::NEAREST);
	////////////////////////////////////////////////////////////////////

	//Button MyFirstButton( 1, 0xffffffff, Test_Tex, 0.0f, 0.0f, 0.4f, 0.4f);
	Button MyFirstButton(Test_Tex, Vector2f(0.0f, 0.0f));
	CompCoords::Initialize(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight());
	
	MyFirstButton.AutoSize();
	Engine::Font* f;
	ExternFileManager::ReadFontFile("fontilein.ttf", 20, Vector2f(0.001f, 0.001f), renderSystem->CreateTexture(""), &f);
	unsigned long long times[100];
	uint counter = 0;
	uint waiting = 30000;
	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

			MyFirstButton.SetSize(100, 50);
			
			//VOLL DIE SCHLEIFE UND SOO

			renderSystem->BeginRendering(new float[4]{ 0.2f, 0.5f, 0.5f, 1.0f });

			renderer->Begin();

			renderer->Submit(MyFirstButton.GetBoxAdress());

			

			if (time++ > 0x0) {
				time = 0x0;
				if (br) r -= 0.5f;
				else r += 0.5f;
				if (bg) g -= 1.0f;
				else g += 1.0f;
				if (bb) b -= 2.0f;
				else b += 2.0f;
			}
			if (r > 255.0f) {
				br = true;
				r -= 0.5f;
			}
			if (g > 255.0f) {
				bg = true;
				g -= 1.0f;
			}
			if (b > 255.0f) {
				bb = true;
				b -= 2.0f;
			}
			if (r < 0.0f) {
				br = false;
				r += 0.5f;
			}
			if (g < 0.0f) {
				bg = false;
				g += 1.0f;
			}
			if (b < 0.0f) {
				bb = false;
				b += 2.0f;
			}
			/*Quad q2(Vector3f(0.0f, -0.8f, 0.0f), Vector2f(0.5, 0.5f), 0xff000000 + ((uint)r) * 0x10000 + ((uint)g) * 0x100 + ((uint)b), NULL);
			renderer->Submit(&q2);*/
			/*renderer->DrawString({ "Hallooo die Engine", f, 0xffffffff }, Vector3f(-1.0f, 0.0f, 0.0f));
			renderer->DrawString({ "suppet tooohhlen Text :)", f, 0xffffffff }, Vector3f(-1.0f, -0.2f, 0.0f));
			renderer->DrawString({ "#Maximilian", f, 0xff00ffff }, Vector3f(-1.0f, -0.4f, 0.0f));*/

			if (MyFirstButton.Click(MOUSE_LEFT))
			{
				MessageBox(NULL, L"IT WOAAAKS!!!", NULL, NULL);
				Inputsystem::GetInstance()->SetMouseOption(Inputsystem::CLICK_RELEASE);
				MyFirstButton.AutoSize();
				MyFirstButton.HStretch();
				//MyFirstButton.AutoCenter();
			}

			renderer->End();
			renderer->Flush();



			renderSystem->EndRendering();
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			//Window::SetConsolePosition(0, 1);
			//std::cout << std::setw(7) << duration << "   " << std::endl << std::setw(7) << 1000000 / duration << "   ";
			if (waiting == 0) {
				times[counter++] = 1000000 / duration;
				if (counter >= 100) {
					unsigned long long x = 0;
					for (int i = 0; i < 100; i++) {
						x += times[i];
					}
					x /= 100;
					std::cout << "FPS: " << x;
					
				}
			} else waiting--;
		}
	};

	renderSystem->Shutdown();
}
