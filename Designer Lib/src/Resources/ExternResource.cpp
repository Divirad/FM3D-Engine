#include "ExternResource.h"
#include "Mesh.h"
#include "ResourceReferences.h"

namespace DesignerLib {



	ExternResource::ExternResource() {
		this->Resources = gcnew ObservableCollection<FoundResource^>();
		this->m_meshPartMap = gcnew Dictionary<FoundResource^, uint>();
	}

	ExternResource::~ExternResource() {
		delete m_loader;
	}

	void ExternResource::Load(System::String^ path, System::String^ resPath) {
		m_resPath = resPath;

		m_loader = new ResourceLoader();
		std::string meshName;
		std::vector<std::string> parts;
		std::vector<bool> animated;
		bool needsSkeleton;
		m_loader->Load(ConvertString(path), meshName, parts, needsSkeleton, animated);
		FoundResource^ mesh = gcnew FoundResource(ConvertString(meshName), ConvertString(meshName), ResourceType::Mesh, this, false);
		this->Resources->Add(mesh);
		int i = 0;
		for (const auto& name : parts) {
			auto part = gcnew FoundResource(ConvertString(name), "", ResourceType::MeshPart, this, animated[i]);
			part->Parent = mesh;
			m_meshPartMap->Add(part, i++);
			mesh->Content->Add(part);
		}
		if (needsSkeleton) {
			auto skeleton = gcnew FoundResource(ConvertString(meshName) + "-Skeleton", ConvertString(meshName) + "-Skeleton", ResourceType::Skeleton, this, false);
			mesh->Content->Add(gcnew FoundResource(mesh, skeleton, this));
			this->Resources->Add(skeleton);
		}

		OnPropertyChanged("Resources");
	}

	ObservableCollection<Mesh^>^ DesignerLib::ExternResource::GetMeshes(Skeleton^% skel) {
		auto result = gcnew ObservableCollection<Mesh^>();
		auto animatedMeshes = gcnew ObservableCollection<Mesh^>();
		auto parts = gcnew ObservableCollection<MeshPart^>();
		
		bool useSkel = false;
		for each(auto res in this->Resources) {
			if (res->ResType == ResourceType::Mesh) {
				parts->Clear();
				useSkel = false;
				for each(auto part in res->Content) {
					if (part->ResType == ResourceType::MeshPart) {
						parts->Add(gcnew MeshPart(part->Name, true, new InternMeshPart(m_loader->GetMeshPart(m_meshPartMap[part]))));
					}
					else if (part->IsReference) {
						if (part->Reference->ResType == ResourceType::Skeleton) {
							useSkel = true;
						}
					}
				}
				auto m = gcnew Mesh(parts, nullptr, res->Name, this->m_resPath + "/" + res->Path + ".fm_mesh");
				result->Add(m);
				if (useSkel) animatedMeshes->Add(m);
			}
		}

		FoundResource^ sres;
		for each(auto res in this->Resources) {
			if (res->ResType == ResourceType::Skeleton) {
				sres = res;
				break;
			}
		}
		if (sres == nullptr) return nullptr;

		auto skeleton = m_loader->GetSkeleton();
		skel = gcnew Skeleton(sres->Name, this->m_resPath + "/" + sres->Path + ".fm_skel", new InternSkeleton(skeleton));
		auto refskel = ResourceReferences::NewSkeleton(skel);

		for each (auto am in animatedMeshes) {
			am->Skelet = refskel;
		}

		return result;
	}

}
