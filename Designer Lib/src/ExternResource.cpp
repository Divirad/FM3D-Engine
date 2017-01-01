#include "ExternResource.h"

DesignerLib::ExternResource::ExternResource() {
	this->Resources = gcnew ObservableCollection<FoundResource^>();
}

DesignerLib::ExternResource::~ExternResource() {
	delete importer;
}

void DesignerLib::ExternResource::Load(System::String^ path) {
	importer = new Assimp::Importer();
	importer->SetPropertyInteger(AI_CONFIG_PP_LBW_MAX_WEIGHTS, 4);
	scene = importer->ReadFile(ConvertString(path).c_str(), aiProcess_LimitBoneWeights | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	if (!scene) FM3D::OUTPUT_ERROR(0, "Assimp Error", "Failed loading " + ConvertString(path));

	if (scene->mNumMeshes != 0) {
		FoundResource^ mesh = gcnew FoundResource("Combined Mesh", "Mesh-Path", FoundResource::Type::Mesh);
		this->Resources->Add(mesh);
		for (uint i = 0U; i < scene->mNumMeshes; i++) {
			std::string name = scene->mMeshes[i]->mName.data;
			OutputDebugStringA(scene->mMeshes[i]->mName.C_Str());
			if (name.length() == 0) {
				name = "Part " + std::to_string(i);
			}
			auto part = gcnew FoundResource(name, name + "-Path", FoundResource::Type::MeshPart);
			mesh->References->Add(gcnew ResourceReference(mesh, part));
			this->Resources->Add(part);
		}
	}


	OnPropertyChanged("Resources");
}
