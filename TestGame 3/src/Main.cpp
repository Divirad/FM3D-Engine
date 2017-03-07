#include <Engine.h>
#include <chrono>
#include <iomanip>
#include "Resources.h"

using ALL_FM3D_NAMESPACES;
using namespace FM3D::Math;

void Move(Camera& camera, Camera& laptop);
Vector3f& SetHill(Vector3f& vec);
Vector3f SetHillNormal(Vector3f& vec);
EntityPtr CreateEntity(EntityCollection&, const Vector3f&, const Vector3f&, const Vector3f&, Model*);
const AnimatedModel* GetModel(EntityPtr& e);
void RenderLaptop(Camera& camera, Resources& res, const EntityPtr& e0, const EntityPtr& e1, const EntityPtr& e2, const EntityPtr& e3);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	Output::Initialize();
	Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE);
	Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);


	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();

	std::string vert = FileManager::ReadShaderFile("src/Graphics/OpenGL3.3/3D/Shader/Light.vert", {});
	std::string vert2 = FileManager::ReadShaderFile("src/Graphics/OpenGL3.3/3D/Shader/Geometry.vert", {});
	auto char0 = vert.back();
	auto char1 = vert2.back();

	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);

	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));

	win->Start(1600, 900, L"TestGame 3");

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
	Camera laptopCam(Vector3f(0.0f, 2.0f, 0.0f));

	Color4f clearColor(0.0f, 0.0f, 0.0f, 1.0f);

	FM3D::Font* font;
	ExternFileManager::ReadFontFile("font.ttf", 50, Vector2f(0.001f, 0.001f), renderSystem, &font);

	Resources res(renderSystem);

	//Entities
	EntityPtr entityLeaves = CreateEntity(scene, Vector3f(20.0f, 0.0f, -10.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(.1f, .1f, .1f), res.treeLeavesModel);
	EntityPtr boba = CreateEntity(scene, Vector3f(5.0f, 3.0f, -5.0f), Vector3f(0.0f, -90.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), res.bobaMesh);
	EntityPtr island = CreateEntity(scene, Vector3f(-35.0f, -0.1f, -15.0f), Vector3f(0.0f, 100.0f, 0.0f), Vector3f(.1f, .1f, .1f), res.islandModel);
	EntityPtr shuttle = CreateEntity(scene, Vector3f(-35.0f, 10.0f, 30.0f), Vector3f(0.0f, -90.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), res.shuttleModel);
	EntityPtr allosaurus = CreateEntity(scene, Vector3f(10.0f, 5.0f, 10.0f), Vector3f(0.0f, -90.0f, 0.0f), Vector3f(.02f, .02f, .02f), res.alloModel);
	EntityPtr laptop = CreateEntity(scene, Vector3f(10.0f, 2.0f, 5.0f), Vector3f(0.0f, -90.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), res.laptopModel);

	//Terrain
	std::vector<uint> indices;
	Vertices vertices(200 * 200 * 4, Vertices::POSITION | Vertices::TEXCOORD | Vertices::NORMAL);
	{
		float size = 1.0f;
		float y = 0.0f;
		int c = 0;
		for (float x = -100.0f; x < 100.0f; x += 1.0f) {
			for (float z = -100.0f; z < 100.0f; z += 1.0f, c += 4) {
				vertices.GetPosition(c + 0) = SetHill(Vector3f(x, 0.0f, z));
				vertices.GetNormal(c + 0) = SetHillNormal(Vector3f(x, 0.0f, z));
				vertices.GetTexCoord(c + 0) = Vector2f(0.0f, 0.0f);
				vertices.GetPosition(c + 1) = SetHill(Vector3f(x, y, z + size));
				vertices.GetNormal(c + 1) = SetHillNormal(Vector3f(x, y, z + size));
				vertices.GetTexCoord(c + 1) = Vector2f(0.0f, 1.0f);
				vertices.GetPosition(c + 2) = SetHill(Vector3f(x + size, y, z + size));
				vertices.GetNormal(c + 2) = SetHillNormal(Vector3f(x + size, y, z + size));
				vertices.GetTexCoord(c + 2) = Vector2f(1.0f, 1.0f);
				vertices.GetPosition(c + 3) = SetHill(Vector3f(x + size, y, z));
				vertices.GetNormal(c + 3) = SetHillNormal(Vector3f(x + size, y, z));
				vertices.GetTexCoord(c + 3) = Vector2f(1.0f, 0.0f);

				indices.push_back(c + 0);
				indices.push_back(c + 1);
				indices.push_back(c + 2);
				indices.push_back(c + 2);
				indices.push_back(c + 3);
				indices.push_back(c + 0);
			}
		}
	}

	Texture* terrainTexture = ExternFileManager::ReadTextureFile("grass.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
	Material terrainMaterial(0xffffffff, terrainTexture, 0.5f, nullptr);
	std::vector<const Material*> materials(1);
	materials[0] = &terrainMaterial;

	Model* terrainModel = new Model(renderSystem->CreateMesh(nullptr, false, std::vector<MeshPart>({ { indices.size(), (void*)&(indices[0]), std::move(vertices), sizeof(uint), false } })), materials);

	EntityPtr terrain = CreateEntity(scene, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), terrainModel);

	//2D
	Text text0{ "", font, 0xff000000 };
	Text text1{ "", font, 0xff000000 };
	Quad textBack(Vector3f(-1.0f, 0.3f, 0.0f), Vector2f(0.4f, 0.3f), 0xfffff00f, res.emptyTex);
	Quad barkQuad(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(0.25, 0.25), 0xffffffff, res.leavesTexture);

	bool resolution = true;

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {
			QueryPerformanceCounter(&time1);

			renderSystem->BeginRendering(clearColor);
			RenderLaptop(laptopCam, res, terrain, allosaurus, island, boba);

			//renderer3D->Submit(entityLeaves.get());
			renderer3D->Submit(boba.get());
			renderer3D->Submit(terrain.get());
			renderer3D->Submit(island.get());
			renderer3D->Submit(shuttle.get());
			renderer3D->Submit(allosaurus.get());
			renderer3D->Submit(laptop.get());
			renderer3D->Flush(camera.GetViewMatrix(), camera.GetPosition());
			//target3D->PresentOnScreen(Vector2i(win->GetWidth(), win->GetHeight()));

			//renderer2D->Begin();

			//Quad renderedScene(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(2.0f, 2.0f), 0xffffffff, target3D->GetTexture());
			//renderer2D->Submit(&renderedScene);

			//renderer2D->Submit(&textBack);
			//renderer2D->Submit(&barkQuad);
			//renderer2D->DrawString(text0, Vector3f(-0.975f, 0.5f, 0.0f));
			//renderer2D->DrawString(text1, Vector3f(-0.975f, 0.4f, 0.0f));
			//renderer2D->End();
			//renderer2D->Flush();
			//target2D->PresentOnScreen(Vector2i(win->GetWidth(), win->GetHeight()));

			target3D->PresentOnScreen(Vector2i(win->GetWidth(), win->GetHeight()));

			renderSystem->EndRendering();

			static_cast<AnimatedModel*>(res.bobaMesh)->AddToAnimationTime(1.0f / 30.0f);
			if (static_cast<AnimatedModel*>(res.bobaMesh)->GetAnimationTime() >= static_cast<AnimatedModel*>(res.bobaMesh)->GetAnimation()->GetDuration())
				static_cast<AnimatedModel*>(res.bobaMesh)->SetAnimationTime(0.0);

			static_cast<AnimatedModel*>(res.shuttleModel)->AddToAnimationTime(1.0f / 60.0f);
			if (static_cast<AnimatedModel*>(res.shuttleModel)->GetAnimationTime() >= static_cast<AnimatedModel*>(res.shuttleModel)->GetAnimation()->GetDuration())
				static_cast<AnimatedModel*>(res.shuttleModel)->SetAnimationTime(0.0);

			static_cast<AnimatedModel*>(res.alloModel)->AddToAnimationTime(1.0f / 15.0f);
			if (static_cast<AnimatedModel*>(res.alloModel)->GetAnimationTime() >= static_cast<AnimatedModel*>(res.alloModel)->GetAnimation()->GetDuration())
				static_cast<AnimatedModel*>(res.alloModel)->SetAnimationTime(0.0);


			Move(camera, laptopCam);
			renderer3D->SetForceWireFrame(Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_F5));

			if (!resolution && Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_N)) {
				std::cout << "---------------------" << std::endl;
				std::cout << "------Higher----------" << std::endl;
				target3D->ReSize(Vector2i(win->GetWidth(), win->GetHeight()));
				resolution = !resolution;
			}
			else if (resolution && Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_M)) {
				std::cout << "---------------------" << std::endl;
				std::cout << "------Smaller--------" << std::endl;
				target3D->ReSize(Vector2i(win->GetWidth() / 4, win->GetHeight() / 4));
				resolution = !resolution;
			}

			camera.Preset(camera.FIRSTPERSON, false);

			QueryPerformanceCounter(&time2);
			LONGLONG time = (1000LL * (time2.QuadPart - time1.QuadPart)) / frequency.QuadPart;
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << 1000.0f / (float)time;
			text0.txt = "FPS: " + stream.str();
			text1.txt = "T: " + std::to_string(time) + "ms";
		}
	};

	renderSystem->Shutdown();
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

Vector3f& SetHill(Vector3f& vec) {
	if (vec.x > 50.0f && vec.x < 75.0f && vec.z > 30.0f && vec.z < 55.0f) {
		float a = 15.0f;
		float b = 2.0f * PI / 50.0f;
		vec.y = a * sin(vec.x * b + (-50.0f * b)) * sin(vec.z * b + (-30.0f * b));
	}
	return vec;
}

Vector3f SetHillNormal(Vector3f& vec) {
	if (vec.x > 50.0f && vec.x < 75.0f && vec.z > 30.0f && vec.z < 55.0f) {
		Vector3f p0 = SetHill(vec + Vector3f::XAxis());
		Vector3f p1 = SetHill(vec - Vector3f::XAxis());
		Vector3f p2 = SetHill(vec + Vector3f::ZAxis());
		Vector3f p3 = SetHill(vec - Vector3f::ZAxis());

		SetHill(vec);

		Vector3f n0 = ((p0 - vec).Cross(p2 - vec)).Normalize();
		Vector3f n1 = ((p1 - vec).Cross(p3 - vec)).Normalize();
		if (n0.y < 0) n0 *= -1.0f;
		if (n1.y < 0) n1 *= -1.0f;

		Vector3f result = (n0 + n1) / 2.0f;

		return result;
	}
	Vector3f r = Vector3f::YAxis();
	return r;
}

EntityPtr CreateEntity(EntityCollection& col, const Vector3f& pos, const Vector3f& rot, const Vector3f& sca, Model* mod) {
	EntityPtr e = col.CreateEntity();
	e->Add<PositionComponent>(pos);
	e->Add<RotationComponent>(rot);
	e->Add<ScaleComponent>(sca);
	e->Add<RenderableComponent>(mod);
	return e;
}
const AnimatedModel* GetModel(EntityPtr& e) {
	RenderableComponent* r = static_cast<RenderableComponent*>(e->GetComponent(RenderableComponentId));
	return static_cast<const AnimatedModel*>(r->GetModel());
}

void RenderLaptop(Camera& camera, Resources& res, const EntityPtr& e0, const EntityPtr& e1, const EntityPtr& e2, const EntityPtr& e3) {
	res.desktopRen3D->Submit(e0.get());
	res.desktopRen3D->Submit(e1.get());
	res.desktopRen3D->Submit(e2.get());
	res.desktopRen3D->Submit(e3.get());
	res.desktopRen3D->Flush(camera.GetViewMatrix(), camera.GetPosition());

	res.desktopRen->Begin();
	Quad renderedScene(Vector3f(-1.0f, -1.0f, 0.0f), Vector2f(2.0f, 2.0f), 0xffffffff, res.desktop3D->GetTexture());
	res.desktopRen->Submit(&renderedScene);
	res.desktopRen->End();
	res.desktopRen->Flush();
}