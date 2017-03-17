#include "Mesh.h"
#include <vector>
#include "../pch.h"
#include <fstream>
#include "../FileWriting.h"
#include "ResourceReferences.h"

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

	MeshPart::MeshPart(System::String^ name, bool vis, InternMeshPart* part) {
		this->Name = name;
		this->Visible = vis;
		m_part = part;
		this->SupportsInstancing = false;
	}

	MeshPart::~MeshPart() {
		delete m_part;
	}

	ObservableCollection<String^>^ MeshPart::Conv(vector<string>* str) {
		if (str == nullptr) return nullptr;
		auto coll = gcnew ObservableCollection<String^>();
		for (const auto& s : *str) {
			coll->Add(ConvertString(s));
		}
		return coll;
	}

	Mesh::Mesh(ObservableCollection<MeshPart^>^ parts, RefSkeleton^ skeleton, String^ name, System::String^ path) {
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
			throw gcnew System::IO::IOException(ConvertString("Failed to write mesh file: " + string(strerror(errno))));
		}

		file.put(5); //File type
		WriteRawToFile(file, Id);	//Resource ID
		WriteRawToFile(file, Name->Length);	//NameLength
		for each (char c in Name) {
			WriteRawToFile(file, c); //Name
		}
		WriteRawToFile(file, Skelet->ID);	//Skeleton ID
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
			throw gcnew System::IO::IOException(ConvertString("Failed to write mesh file: " + string(strerror(errno))));
		}

		file.put(3); //File type
		WriteRawToFile(file, Id);	//Resource ID
		WriteRawToFile(file, Skelet->ID); //Skeleton ID
		WriteRawToFile(file, SupportsInstancing); //Supports Instancing
		WriteRawToFile(file, Parts->Count);	//Parts Count
		for each(auto p in Parts) {
			p->GetIntern()->WriteToFile(file); //Parts
		}
	}

	Mesh^ Mesh::FromFile(String^ path) {
		bool isDesignerFile = false;
		std::ifstream file;
		file.open(ConvertString(path), ios::in | ios::binary);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException(ConvertString("Failed to open mesh file: " + string(strerror(errno))));
		}
		byte type = ReadRawFromFile<byte>(file);	//File type
		if (type == 5) isDesignerFile = true;
		else if(type != 3) throw gcnew System::ArgumentException("File is not a mesh file!");
		unsigned int resourceId = ReadRawFromFile<unsigned int>(file); //Resource ID
		std::string name = "Unknown";
		if (isDesignerFile)
			name = ReadRawFromFile<std::string>(file);	//Name
		unsigned int skeletonId = ReadRawFromFile<unsigned int>(file); //Skeleton ID
		bool supportsInstancing = ReadRawFromFile<bool>(file);	//Supports instancing
		int partsCount = ReadRawFromFile<int>(file); //Parts Count
		auto parts = gcnew ObservableCollection<MeshPart^>();
		for (int i = 0; i < partsCount; i++) {
			std::string pname = "Unknown";
			if (isDesignerFile)
				pname = ReadRawFromFile<std::string>(file);	//Part Name
			auto meshp = InternMeshPart::FromFile(file); //Parts
			parts->Add(gcnew MeshPart(ConvertString(pname), true, meshp));
		}
		return gcnew Mesh(parts, ResourceReferences::GetSkeleton(skeletonId), ConvertString(name), path);
	}

	void Mesh::OnPartChanged(System::Object^ sender, System::ComponentModel::PropertyChangedEventArgs^ e) {
		throw gcnew System::NotImplementedException();
	}

	RefMesh::RefMesh(System::String^ path) {
		_Path = path;
		bool isDesignerFile = false;
		std::ifstream file;
		file.open(ConvertString(_Path), ios::in | ios::binary);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException(ConvertString("Failed to open mesh file: " + string(strerror(errno))));
		}
		byte type = ReadRawFromFile<byte>(file);	//File type
		if (type == 5) isDesignerFile = true;
		else if (type != 3) throw gcnew System::ArgumentException("File is not a mesh file!");
		_ID = ReadRawFromFile<unsigned int>(file); //Resource ID
		std::string name = "Unknown";
		if (isDesignerFile)
			name = ReadRawFromFile<std::string>(file);	//Name
		_Name = ConvertString(name);
		file.close();
	}

	RefMesh::RefMesh(Mesh^ mesh) {
		_Path = mesh->Path;
		_Name = mesh->Name;
		_ID = mesh->Id;
		m_target = gcnew System::WeakReference(mesh);
		Target->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &RefMesh::OnMeshChanged);
	}

	void RefMesh::OnMeshChanged(System::Object^ sender, System::ComponentModel::PropertyChangedEventArgs^ e) {
		if (e->PropertyName == "Name") {
			_Name = Target->Name;
			OnPropertyChanged("Name");
		}
		else if (e->PropertyName == "Id") {
			_ID = Target->Id;
			OnPropertyChanged("ID");
		}
		else if (e->PropertyName == "Path") {
			_Path = Target->Path;
			OnPropertyChanged("Path");
		}
	}

	void RefMesh::Load() {
		m_target = gcnew WeakReference(Mesh::FromFile(_Path));
		Target->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &RefMesh::OnMeshChanged);
		if (_Path != Target->Path) OnPropertyChanged("Path");
		if (_ID != Target->Id) OnPropertyChanged("ID");
		if (_Name != Target->Name) OnPropertyChanged("Name");
	}

}