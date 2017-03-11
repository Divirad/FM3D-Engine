#include "Mesh.h"
#include <vector>
#include "../pch.h"
#include <fstream>
#include "../FileWriting.h"

using namespace System::Collections::ObjectModel;
using namespace System;
using namespace std;

namespace DesignerLib {

	Vertex::Vertex(const InternVertex* v) {
		this->Position = v->position.empty() ? nullptr : ConvertString(v->position);
		this->TexCoord = v->texCoord.empty() ? nullptr : ConvertString(v->texCoord);
		this->Normal = v->normal.empty() ? nullptr : ConvertString(v->normal);
		this->Color = v->color.empty() ? nullptr : ConvertString(v->color);
		this->BoneIndex = v->boneIndex.empty() ? nullptr : ConvertString(v->boneIndex);
		this->BoneWeight = v->boneWeight.empty() ? nullptr : ConvertString(v->boneWeight);
		this->Tangent = v->tangent.empty() ? nullptr : ConvertString(v->tangent);
	}

	MeshPart::MeshPart(System::String^ name, bool vis, FM3D::MeshPart* part) {
		this->Name = name;
		this->Visible = vis;
		m_part = new InternMeshPart(part);
		this->SupportsInstancing = false;
	}

	ObservableCollection<String^>^ MeshPart::Conv(vector<string>* str) {
		if (str == nullptr) return nullptr;
		auto coll = gcnew ObservableCollection<String^>();
		for (const auto& s : *str) {
			coll->Add(ConvertString(s));
		}
		return coll;
	}

	Mesh::Mesh(ObservableCollection<MeshPart^>^ parts, Skeleton^ skeleton, String^ name, System::String^ path) {
		this->Parts = gcnew ObservableCollection<MeshPart^>();
		for each(auto p in parts) {
			this->Parts->Add(p);
			p->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &Mesh::OnPartChanged);
		}
		this->Skelet = skeleton;
		this->IsSaved = false;
		this->Name = name;
		this->Path = path;
		this->Id = 0xffffffff;
	}

	void Mesh::WriteToFile() {
		std::ofstream file(ConvertString(this->Path), ios::out | ios::binary | ios::trunc);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException("Failed to write mesh file");
		}

		file.put(5); //File type
		WriteRawToFile(file, Id);	//Resource ID
		WriteRawToFile(file, Name->Length);	//NameLength
		for each (char c in Name) {
			WriteRawToFile(file, c); //Name
		}
		WriteRawToFile(file, Skelet->Id);	//Skeleton ID
		WriteRawToFile(file, SupportsInstancing); //Supports Instancing
		WriteRawToFile(file, Parts->Count);	//Parts Count
		for each(auto p in Parts) {
			WriteRawToFile(file, p->Name->Length);	//Part NameLength
			for each (char c in p->Name) {
				WriteRawToFile(file, c); //Part Name
			}
			p->GetIntern()->WriteToFile(file); //Parts
		}
	}

	void Mesh::ExportToFile() {
		std::ofstream file(ConvertString(this->Path), ios::out | ios::binary | ios::trunc);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException("Failed to write mesh file");
		}

		file.put(3); //File type
		WriteRawToFile(file, Id);	//Resource ID
		WriteRawToFile(file, Skelet->Id); //Skeleton ID
		WriteRawToFile(file, SupportsInstancing); //Supports Instancing
		WriteRawToFile(file, Parts->Count);	//Parts Count
		for each(auto p in Parts) {
			p->GetIntern()->WriteToFile(file); //Parts
		}
	}

	void Mesh::OnPartChanged(System::Object^ sender, System::ComponentModel::PropertyChangedEventArgs^ e) {
		throw gcnew System::NotImplementedException();
	}

}