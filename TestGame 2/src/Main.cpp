#include <Engine.h>
#include <chrono>
#include <iomanip>

using ALL_FM3D_NAMESPACES;
using namespace FM3D::Math;

void Move(Camera& camera);

EntityPtr CreateEntity(EntityCollection&, const Vector3f&, const Vector3f&, const Vector3f&, Model*);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	Output::Initialize();
	Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE);
	Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);


	FileManager::Initialize("../Testgame 3/res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();

	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(1920, 1080, L"TestGame 3");

	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	Matrix4f projectionMatrix = Matrix4f::ProjectionFOV(70.0f, static_cast<float>(win->GetWidth()) / static_cast<float>(win->GetHeight()), 0.1f, 1000.0f);

	RenderTarget2D* target3D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer3D* renderer3D = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight(), target3D);

	EntityCollection scene;

	Camera camera(Vector3f(-5.4f, 7.4f, -6.8f));

	Color4f clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Model* alloModel;
	Texture* texAllo;
	Texture* normalAllo;
	Material matAllo;
	Material matAllo2;

	ExternFileManager::ReadModelFile("allo.fbx", renderSystem, &alloModel, false, true);
	AnimatedModel* bobaAnimModel = (AnimatedModel*)alloModel;
	bobaAnimModel->SetAnimation(&alloModel->GetMesh()->GetSkeleton()->GetAnimations()[0]);
	bobaAnimModel->SetAnimationTime(1.5);

	texAllo = ExternFileManager::ReadTextureFile("Allosaurus_diffuse.TGA", renderSystem, Texture::LINEAR, Texture::REPEAT);
	normalAllo = ExternFileManager::ReadTextureFile("Allosaurus_normals.TGA", renderSystem, Texture::LINEAR, Texture::REPEAT);

	matAllo = Material(0xffffffff, texAllo, 0.7f, nullptr, normalAllo);
	matAllo2 = Material(0xffffffff, texAllo, 0.7f, nullptr, nullptr);
	alloModel->GetMaterials()[0] = &matAllo;

	AnimatedModel* alloModel2 = new AnimatedModel(alloModel->GetMesh(), std::vector<const Material*>({ &matAllo2 }), &alloModel->GetMesh()->GetSkeleton()->GetAnimations()[0], 1.5);

	//Entities
	EntityPtr allosaurus = CreateEntity(scene, Vector3f(0.0f, 1.0f, -8.0f), Vector3f(0.0f, -90.0f, 0.0f), Vector3f(.02f, .02f, .02f), alloModel2);
	EntityPtr allosaurus2 = CreateEntity(scene, Vector3f(7.0f, 1.0f, -10.0f), Vector3f(0.0f, -70.0f, 0.0f), Vector3f(.02f, .02f, .02f), alloModel2);
	
	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			renderSystem->BeginRendering(clearColor);

			renderer3D->Submit(allosaurus.get());
			//renderer3D->Submit(allosaurus2.get());
			renderer3D->Flush(camera.GetViewMatrix(), camera.GetPosition());

			target3D->PresentOnScreen(Vector2i(win->GetWidth(), win->GetHeight()));

			renderSystem->EndRendering();

			Move(camera);
		}
	};

	renderSystem->Shutdown();
}

EntityPtr CreateEntity(EntityCollection& col, const Vector3f& pos, const Vector3f& rot, const Vector3f& sca, Model* mod) {
	EntityPtr e = col.CreateEntity();
	e->Add<PositionComponent>(pos);
	e->Add<RotationComponent>(rot);
	e->Add<ScaleComponent>(sca);
	e->Add<RenderableComponent>(mod);
	return e;
}

void Move(Camera& camera) {
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
