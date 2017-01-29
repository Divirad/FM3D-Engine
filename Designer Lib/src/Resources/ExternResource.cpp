#include "ExternResource.h"
#include "Mesh.h"

namespace DesignerLib {



	ExternResource::ExternResource() {
		this->Resources = gcnew ObservableCollection<FoundResource^>();
		this->m_meshPartMap = gcnew Dictionary<FoundResource^, uint>();
	}

	ExternResource::~ExternResource() {
		delete m_loader;
	}

	void ExternResource::Load(System::String^ path) {
		m_loader = new ResourceLoader();
		std::string meshName;
		std::vector<std::string> parts;
		m_loader->Load(ConvertString(path), meshName, parts);
		FoundResource^ mesh = gcnew FoundResource(ConvertString(meshName), "Mesh-Path", ResourceType::Mesh, this);
		this->Resources->Add(mesh);
		int i = 0;
		for (const auto& name : parts) {
			auto part = gcnew FoundResource(name, name + "-Path", ResourceType::MeshPart, this);
			part->Parent = mesh;
			m_meshPartMap->Add(part, i++);
			mesh->Content->Add(part);
		}

		OnPropertyChanged("Resources");
	}

	ObservableCollection<Mesh^>^ DesignerLib::ExternResource::GetMeshes() {
		auto result = gcnew ObservableCollection<Mesh^>();
		auto parts = gcnew ObservableCollection<MeshPart^>();
		for each(auto res in this->Resources) {
			parts->Clear();
			for each(auto part in res->Content) {
				if (part->ResType == ResourceType::MeshPart) {
					parts->Add(gcnew MeshPart(part->Name, true, m_loader->GetMeshPart(m_meshPartMap[part])));
				}
			}
			result->Add(gcnew Mesh(parts));
		}
		return result;
	}

}
