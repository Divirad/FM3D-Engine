#pragma once
#include <Engine.h>

using namespace Engine;

struct Resources {

#pragma region
	Texture* emptyTex;
	Material emptyMat;
	void Init(RenderSystem* renderSystem) {
		emptyTex = renderSystem->CreateTexture();
		float pixels[] = {
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f
		};
		emptyTex->Initialize(2, 2, Texture::NEAREST, Texture::CLAMP, Texture::NONE, pixels, 32);
		emptyMat = { 0xffffffff, emptyTex };
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
		ExternFileManager::ReadModelFile("island/island.dae", renderSystem, &islandModel, false, true);

		islandTexture0 = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("island/arl1b.jpg", islandTexture0, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);

		islandTexture1 = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("island/grs1.jpg", islandTexture1, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);

		islandTexture2 = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("island/lv1.jpg", islandTexture2, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);

		islandTexture3 = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("island/plvs1c.jpg", islandTexture3, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);

		islandTexture4 = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("island/rc1.jpg", islandTexture4, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		
		islandTexture5 = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("island/snd1.jpg", islandTexture5, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);


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

		bobaTexBody = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("Fett_body_D.tga", bobaTexBody, Texture::NEAREST);
		bobaTexJet = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("Fett_jetpak_D.tga", bobaTexJet, Texture::NEAREST);
		bobaTexHelmet = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("Fett_helmet_D.tga", bobaTexHelmet, Texture::NEAREST);
		bobaTexDisplay = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("Fett_display_D.tga", bobaTexDisplay, Texture::NEAREST);

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
		
		leavesTexture = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("leaves.png", leavesTexture, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);
		barkTexture = renderSystem->CreateTexture();
		ExternFileManager::ReadTextureFile("bark.jpg", barkTexture, Texture::LINEAR, Texture::REPEAT, Texture::MIPMAP_LINEAR);

		barkMaterial = { 0xffffffff, barkTexture };
		leavesMaterial = { 0xffffffff, leavesTexture };

		treeLeavesModel->GetMaterials()[0] = &barkMaterial;
		treeLeavesModel->GetMaterials()[1] = &leavesMaterial;
	}
#pragma endregion

public:
	Resources(RenderSystem* r) {
		Init(r);
		InitIsland(r);
		InitBoba(r);
		InitTree(r);
	}
};