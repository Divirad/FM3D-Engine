#pragma once
#include <Engine.h>

using namespace FM3D;

struct Resources {

#pragma region
	Texture* emptyTex;
	Material emptyMat;
	Texture* redTex;
	Material redMat;
	Texture* greenTex;
	Material greenMat;
	Texture* blueTex;
	Texture* blue1Tex;
	Texture* blue2Tex;
	Material blueMat;
	Texture* greyTex;
	Material greyMat;
	Texture* disabledTex;
	Material disabledMat;
	void Init(RenderSystem* renderSystem) {
		{
			float pixels[] = {
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f
			};
			emptyTex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
			emptyMat = { 0xffffffff, emptyTex };
		}
		{
			float pixels[] = {
				0.0f, 0.0f, 1.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 1.0f
			};
			redTex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
			redMat = { 0xffffffff, redTex };
		}
		{
			float pixels[] = {
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f
			};
			disabledTex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::CLAMP, Texture::NONE, pixels, 32);
			disabledMat = { 0x0, disabledTex };
		}
		{
			float pixels[] = {
				0.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 0.0f, 1.0f
			};
			greenTex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
			greenMat = { 0xffffffff, greenTex };
		}
		{
			float pixels[] = {
				1.0f, 0.0f, 0.0f, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f,
				1.0f, 0.0f, 0.0f, 1.0f
			};
			blueTex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
			blueMat = { 0xffffffff, blueTex };
		}
		{
			float pixels[] = {
				1.0f, 0.46f, 0.0f, 1.0f,
				1.0f, 0.46f, 0.0f, 1.0f,
				1.0f, 0.46f, 0.0f, 1.0f,
				1.0f, 0.46f, 0.0f, 1.0f
			};
			blue1Tex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
		}
		{
			float pixels[] = {
				1.0f, 0.0f, 0.46f, 1.0f,
				1.0f, 0.0f, 0.46f, 1.0f,
				1.0f, 0.0f, 0.46f, 1.0f,
				1.0f, 0.0f, 0.46f, 1.0f
			};
			blue2Tex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
		}
		{
			float pixels[] = {
				0.35f, 0.35f, 0.35f, 1.0f,
				0.35f, 0.35f, 0.35f, 1.0f,
				0.35f, 0.35f, 0.35f, 1.0f,
				0.35f, 0.35f, 0.35f, 1.0f
			};
			greyTex = renderSystem->CreateTexture(2, 2, Texture::NEAREST, Texture::REPEAT, Texture::NONE, pixels, 32);
			greyMat = { 0xffffffff, greyTex };
		}
	}
#pragma endregion

#pragma region Tropical Island
	Model* islandModel;
	Texture* islandTexture0;
	Material islandMaterial0;
	Texture* islandTexture1;
	Material islandMaterial1;
	Texture* islandTexture2;
	Material islandMaterial2;
	Texture* islandTexture3;
	Material islandMaterial3;
	Texture* islandTexture4;
	Material islandMaterial4;
	Texture* islandTexture5;
	Material islandMaterial5;

	void InitIsland(RenderSystem* renderSystem) {
		ExternFileManager::
			ReadModelFile("island/island.dae", renderSystem, &islandModel, false, true);

		islandTexture0 = ExternFileManager::ReadTextureFile("island/arl1b.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		islandTexture1 = ExternFileManager::ReadTextureFile("island/grs1.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		islandTexture2 = ExternFileManager::ReadTextureFile("island/lv1.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		islandTexture3 = ExternFileManager::ReadTextureFile("island/plvs1c.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		islandTexture4 = ExternFileManager::ReadTextureFile("island/rc1.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		islandTexture5 = ExternFileManager::ReadTextureFile("island/snd1.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);


		islandMaterial0 = { 0xffffffff, islandTexture0 };
		islandMaterial1 = { 0xffffffff, islandTexture1 };
		islandMaterial2 = { 0xffffffff, islandTexture2 };
		islandMaterial3 = { 0xffffffff, islandTexture3 };
		islandMaterial4 = { 0xffffffff, islandTexture4 };
		islandMaterial5 = { 0xffffffff, islandTexture5 };

		auto& materials = islandModel->GetMaterials();
		materials[0] = &islandMaterial0;
		materials[1] = &islandMaterial3;
		materials[2] = &islandMaterial5;
		materials[3] = &islandMaterial1;
		materials[4] = &islandMaterial4;
		materials[5] = &islandMaterial2;
	}
#pragma endregion

#pragma region Boba Fett
	Model* bobaMesh;
	Texture* bobaTexBody;
	Texture* bobaTexJet;
	Texture* bobaTexHelmet;
	Texture* bobaTexDisplay;
	Material mat1Boba;
	Material mat2Boba;
	Material mat3Boba;
	Material mat4Boba;
	Material mat5Boba;
	void InitBoba(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("bobaFett.dae", renderSystem, &bobaMesh, false, true);
		AnimatedModel* bobaAnimModel = (AnimatedModel*)bobaMesh;
		bobaAnimModel->SetAnimation(&bobaMesh->GetMesh()->GetSkeleton()->GetAnimations()[0]);
		bobaAnimModel->SetAnimationTime(1.5);

		bobaTexBody = ExternFileManager::ReadTextureFile("Fett_body_D.tga", renderSystem, Texture::NEAREST);
		bobaTexJet = ExternFileManager::ReadTextureFile("Fett_jetpak_D.tga", renderSystem, Texture::NEAREST);
		bobaTexHelmet = ExternFileManager::ReadTextureFile("Fett_helmet_D.tga", renderSystem, Texture::NEAREST);
		bobaTexDisplay = ExternFileManager::ReadTextureFile("Fett_display_D.tga", renderSystem, Texture::NEAREST);

		mat1Boba = { 0xffffffff, bobaTexJet };
		mat2Boba = { 0xffffffff, bobaTexDisplay };
		mat3Boba = { 0xffffffff, bobaTexHelmet };
		mat4Boba = { 0xffffffff, bobaTexJet };
		mat5Boba = { 0xffffffff, bobaTexBody };

		auto& materialsBoba = bobaMesh->GetMaterials();
		materialsBoba[0] = &mat1Boba;
		materialsBoba[1] = &mat2Boba;
		materialsBoba[2] = &mat3Boba;
		materialsBoba[3] = &mat4Boba;
		materialsBoba[4] = &mat5Boba;
	}
#pragma endregion

#pragma region Tree
	Model* treeLeavesModel;
	Texture* leavesTexture;
	Texture* barkTexture;
	Material barkMaterial;
	Material leavesMaterial;
	void InitTree(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("Tree.dae", renderSystem, &treeLeavesModel, false, true, Matrix4f::Translate(Vector3f(850.0f, 0.0f, 0.0f)));

		leavesTexture = ExternFileManager::ReadTextureFile("leaves.png", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		barkTexture = ExternFileManager::ReadTextureFile("bark.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);

		barkMaterial = { 0xffffffff, barkTexture };
		leavesMaterial = { 0xffffffff, leavesTexture };

		treeLeavesModel->GetMaterials()[0] = &barkMaterial;
		treeLeavesModel->GetMaterials()[1] = &leavesMaterial;
	}
#pragma endregion

#pragma region Allosaurus
	Model* alloModel;
	Texture* texAllo;
	Texture* normalAllo;
	Material matAllo;
	void InitAllo(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("allo.fbx", renderSystem, &alloModel, false, true);
		AnimatedModel* bobaAnimModel = (AnimatedModel*)alloModel;
		bobaAnimModel->SetAnimation(&alloModel->GetMesh()->GetSkeleton()->GetAnimations()[0]);
		bobaAnimModel->SetAnimationTime(1.5);
		texAllo = ExternFileManager::ReadTextureFile("Allosaurus_diffuse.TGA", renderSystem, Texture::LINEAR, Texture::REPEAT);
		normalAllo = ExternFileManager::ReadTextureFile("Allosaurus_normals.TGA", renderSystem, Texture::LINEAR, Texture::REPEAT);
		matAllo = Material(0xffffffff, texAllo, 0.7f, nullptr, normalAllo);
		alloModel->GetMaterials()[0] = &matAllo;
	}
#pragma endregion 

#pragma region Ring
	Model* ringModel;
	Texture* texRing;
	Texture* normalRing;
	Material matRing;
	void InitRing(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("Ring_Of_Doom.obj", renderSystem, &ringModel, false, true);
		texRing = ExternFileManager::ReadTextureFile("Ring_Of_Doom_Texture.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT);
		normalRing = ExternFileManager::ReadTextureFile("Ring_Of_Doom_Normal.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT);
		matRing = Material(0xffffffff, texRing, 0.7f, nullptr, normalRing);
		ringModel->GetMaterials()[0] = &matRing;
	}
#pragma endregion 

#pragma region Shuttle
	Model* shuttleModel;
	Texture* shuttleBody;
	Texture* shuttleHover;
	Texture* shuttleInside;
	Texture* shuttleLegs;
	Texture* shuttleRest;
	Texture* shuttleSite;
	Texture* shuttleWire;
	Texture* shuttleOutside;
	Texture* shuttleBuster;
	Material matShuttleBody;
	Material matShuttleHover;
	Material matShuttleInside;
	Material matShuttleLegs;
	Material matShuttleRest;
	Material matShuttleSite;
	Material matShuttleWire;
	Material matShuttleOutside;
	Material matShuttleBuster;
	void InitShuttle(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("shuttle.dae", renderSystem, &shuttleModel, false, true);
		AnimatedModel* shuttleAnimModel = (AnimatedModel*)shuttleModel;
		shuttleAnimModel->SetAnimation(&shuttleModel->GetMesh()->GetSkeleton()->GetAnimations()[0]);
		shuttleAnimModel->SetAnimationTime(0.0);

		shuttleBody = ExternFileManager::ReadTextureFile("Shuttle_Body_Outside_Col Kopie.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleHover = ExternFileManager::ReadTextureFile("Shuttle_Hover_Col.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleInside = ExternFileManager::ReadTextureFile("Shuttle_Inside_Col.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleLegs = ExternFileManager::ReadTextureFile("Shuttle_Legs_Col.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleRest = ExternFileManager::ReadTextureFile("Shuttle_Rest_Col.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleSite = ExternFileManager::ReadTextureFile("Shuttle_Site_Col.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleWire = ExternFileManager::ReadTextureFile("Shuttle_Wire_Col.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleOutside = ExternFileManager::ReadTextureFile("Shuttle_Body_Outside_Col Kopie.png.001.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		shuttleBuster = ExternFileManager::ReadTextureFile("Buster_Col_1.jpg", renderSystem, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);


		matShuttleBody = { 0xffffffff, shuttleBody };
		matShuttleHover = { 0xffffffff, shuttleHover };
		matShuttleInside = { 0xffffffff, shuttleInside };
		matShuttleLegs = { 0xffffffff, shuttleLegs };
		matShuttleRest = { 0xffffffff, shuttleRest };
		matShuttleSite = { 0xffffffff, shuttleSite };
		matShuttleWire = { 0xffffffff, shuttleWire };
		matShuttleOutside = { 0xffffffff, shuttleOutside };
		matShuttleBuster = { 0xffffffff, shuttleBuster };

		auto& materials = shuttleModel->GetMaterials();
		materials[0] = &disabledMat; //strange thing
		materials[1] = &matShuttleBuster;
		materials[2] = &emptyMat; //unknown
		materials[3] = &matShuttleOutside;
		materials[4] = &matShuttleWire;
		materials[5] = &matShuttleLegs;
		materials[6] = &matShuttleRest;
		materials[7] = &matShuttleInside;
		materials[8] = &matShuttleBody;
		materials[9] = &matShuttleInside;
		materials[10] = &emptyMat; //unknown
		materials[11] = &matShuttleHover;
	}
#pragma endregion

#pragma region Fir

	Model* firModel;
	Model* firModel2;
	Texture* firTex0;
	Texture* firTex1;
	Material firMat0;
	Material firMat1;
	Material firMat2;
	void InitFir(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("firtree1.3ds", renderSystem, &firModel, false, true);
		firTex0 = ExternFileManager::ReadTextureFile("nadeln.png", renderSystem, Texture::LINEAR, Texture::REPEAT);
		firTex1 = ExternFileManager::ReadTextureFile("stamm2.png", renderSystem, Texture::LINEAR, Texture::REPEAT);
		firMat0 = Material(0xffffffff, firTex0);
		firMat1 = Material(0xffffffff, firTex1);
		firModel->GetMaterials()[2] = &firMat0;
		firModel->GetMaterials()[1] = &firMat1;
		firModel->GetMaterials()[0] = &firMat1;
		firMat2 = Material(0xffff0000, firTex0);
		firModel2 = new Model(firModel->GetMesh(), std::vector<const Material*> { &firMat1, &firMat1, &firMat2 });
	}
#pragma endregion

#pragma region Laptop
	Model* laptopModel;
	Material desktopMat;
	const Texture* desktopTex;
	RenderTarget2D* desktop;
	RenderTarget2D* desktop3D;
	Renderer2D* desktopRen;
	Renderer3D* desktopRen3D;

	void InitLaptop(RenderSystem* renderSystem) {
		ExternFileManager::ReadModelFile("tv.dae", renderSystem, &laptopModel, false, false);

		desktop = renderSystem->CreateRenderTarget2D(Vector2i(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight()), true);
		desktopRen = renderSystem->CreateRenderer2D(desktop);
		desktop3D = renderSystem->CreateRenderTarget2D(Vector2i(Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight()), true);
		desktopRen3D = renderSystem->CreateRenderer3D(Matrix4f::ProjectionFOV(70.0f, (float)Window::GetInstance()->GetWidth() / (float)Window::GetInstance()->GetHeight(), 0.1f, 10000.0f), Window::GetInstance()->GetWidth(), Window::GetInstance()->GetHeight(), desktop3D);
		desktopTex = desktop->GetTexture();

		desktopMat = { 0xffffffff, desktopTex };

		auto& materials = laptopModel->GetMaterials();
		materials[0] = &greyMat;
		materials[1] = &desktopMat;
	}
#pragma endregion

#pragma region Skybox
	Model* skyModel;
	Texture* texSky0;
	Texture* texSky1;
	Texture* texSky2;
	Texture* texSky3;
	Texture* texSky4;
	Texture* texSky5;
	std::vector<Material> skyMaterials;
	void InitSky(RenderSystem* renderSystem) {
		texSky0 = ExternFileManager::ReadTextureFile("mossymountains_left.tif", renderSystem, Texture::LINEAR, Texture::CLAMP_TO_EDGE);
		texSky1 = ExternFileManager::ReadTextureFile("mossymountains_front.tif", renderSystem, Texture::LINEAR, Texture::CLAMP_TO_EDGE);
		texSky2 = ExternFileManager::ReadTextureFile("mossymountains_right.tif", renderSystem, Texture::LINEAR, Texture::CLAMP_TO_EDGE);
		texSky3 = ExternFileManager::ReadTextureFile("mossymountains_back.tif", renderSystem, Texture::LINEAR, Texture::CLAMP_TO_EDGE);
		texSky4 = ExternFileManager::ReadTextureFile("mossymountains_down.tif", renderSystem, Texture::LINEAR, Texture::CLAMP_TO_EDGE);
		texSky5 = ExternFileManager::ReadTextureFile("mossymountains_up.tif", renderSystem, Texture::LINEAR, Texture::CLAMP_TO_EDGE);

		skyMaterials.emplace_back(0xffffffff, texSky0);
		skyMaterials.emplace_back(0xffffffff, texSky1);
		skyMaterials.emplace_back(0xffffffff, texSky2);
		skyMaterials.emplace_back(0xffffffff, texSky3);
		skyMaterials.emplace_back(0xffffffff, texSky4);
		skyMaterials.emplace_back(0xffffffff, texSky5);

		std::vector<const Material*> materials;
		for (const auto& m : skyMaterials) materials.push_back(&m);

		skyModel = new Model(MeshCreator::CreateCube(renderSystem, Vector3f(0.0f, 0.0f, 0.0f), 1.0f), materials);
	}
public:
	Resources(RenderSystem* r) {
		Init(r);
		std::cout << "Load Allosaurus..." << std::endl;
		InitAllo(r);
		//InitIsland(r);
		//InitBoba(r);
		//InitTree(r);
		//InitShuttle(r);
		//InitLaptop(r);
		std::cout << "Load Ring..." << std::endl;
		InitRing(r);
		std::cout << "Load Skybox..." << std::endl;
		InitSky(r);
		std::cout << "Load Fir Tree..." << std::endl;
		InitFir(r);
	}
};