#include <Engine.h>
#include <chrono>
#include <iomanip>

using namespace Engine;

void StarwarsScene(HINSTANCE hInstance);


///////////////////////////////////////////////////////////////
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	StarwarsScene(hInstance);
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
	AnimatedModel* bobaAnimModel = (AnimatedModel*)bobaMesh;
	bobaAnimModel->SetAnimation(&bobaMesh->GetMesh()->GetSkeleton()->GetAnimations()[0]);
	bobaAnimModel->SetAnimationTime(1.5);

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

	std::vector<std::vector<Entity>> entities;

	for (int x = 0; x < 50; x++) {
		entities.push_back(std::vector<Entity>());
		for (int z = 0; z < 100; z++) {
			entities[x].push_back(Entity(Vector3f(x * 2.5f, 0.0f, z * 2.5f), Vector3f(180.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), bobaMesh));
		}
	}

	Entity boba(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(180.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), bobaMesh);
	boba.GetAnimations().push_back({ 0u, 0.0 });

	float color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	Camera camera(Vector3f(25.0f * 2.5f, 10.0f, 50.0f * 2.5f), Vector3f(-45.0f, 0.0f, 0.0f));

	LARGE_INTEGER time1;
	LARGE_INTEGER time2;

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			QueryPerformanceCounter(&time1);

			renderSystem->BeginRendering(color);

			//renderer->Submit(&trooper1);
			//renderer->Submit(&trooper2);
			//renderer->Submit(&boba);

			for (std::vector<Entity>& ent : entities) {
				for (Entity& e : ent) {
					renderer->Submit(&e);
				}
			}

			renderer->Flush(camera.GetViewMatrix(), camera.GetPosition());

			renderSystem->EndRendering();
			//((AnimatedModel*)boba.GetModel())->AddToAnimationTime(1.0 / 60.0);
			if (((AnimatedModel*)boba.GetModel())->GetAnimationTime() >= ((AnimatedModel*)boba.GetModel())->GetAnimation()->GetDuration())
				((AnimatedModel*)boba.GetModel())->SetAnimationTime(0.0);

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

			QueryPerformanceCounter(&time2);
			std::cout << time2.QuadPart - time1.QuadPart << std::endl;

		}
	};

	renderSystem->Shutdown();
}
