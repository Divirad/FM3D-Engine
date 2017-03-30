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
	
//http://tf3dm.com/3d-model/dream-small-tropical-island-32665.html
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

public:
	Resources(RenderSystem* r) {
		Init(r);
		InitIsland(r);
	}
};