#include "Skeleton.h"
#include <fstream>
#include "../pch.h"
#include "../FileWriting.h"

namespace DesignerLib {

	RefSkeleton::RefSkeleton(System::String^ path) {
		_Path = path;
		bool isDesignerFile = false;
		std::ifstream file(ConvertString(_Path), std::ios::in | std::ios::binary);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException(ConvertString("Failed to open skeleton file: " + std::string(strerror(errno))));
		}
		byte type = ReadRawFromFile<byte>(file);	//File type
		if (type == 5) isDesignerFile = true;
		else if (type != 3) throw gcnew System::ArgumentException("File is not a skeleton file!");
		_ID = ReadRawFromFile<unsigned int>(file); //Resource ID
		std::string name = "Unknown";
		if (isDesignerFile)
			name = ReadRawFromFile<std::string>(file);	//Name
		_Name = ConvertString(name);
		file.close();
	}

	RefSkeleton::RefSkeleton(Skeleton^ skel) {
		_Path = skel->Path;
		_Name = skel->Name;
		_ID = skel->Id;
		m_target = gcnew System::WeakReference(skel);
		skel->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &RefSkeleton::OnSkelChanged);
	}

	void RefSkeleton::OnSkelChanged(System::Object ^ sender, System::ComponentModel::PropertyChangedEventArgs ^ e) {
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

	void RefSkeleton::Load() {
		m_target = gcnew System::WeakReference(Skeleton::FromFile(_Path));
		Target->PropertyChanged += gcnew System::ComponentModel::PropertyChangedEventHandler(this, &RefSkeleton::OnSkelChanged);
		if (_Path != Target->Path) OnPropertyChanged("Path");
		if (_ID != Target->Id) OnPropertyChanged("ID");
		if (_Name != Target->Name) OnPropertyChanged("Name");
	}

	Skeleton::Skeleton(System::String^ name, System::String^ path, InternSkeleton* skeleton) {
		this->m_skeleton = skeleton;
		this->Name = name;
		this->Id = 0xffffffff;
		this->Path = path;
		this->IsSaved = false;
	}

	void Skeleton::WriteToFile() {
		std::ofstream file(ConvertString(this->Path), std::ios::out | std::ios::binary | std::ios::trunc);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException(ConvertString("Failed to write skeleton file: " + std::string(strerror(errno))));
		}

		file.put(5); //File type
		WriteRawToFile(file, Id);	//Resource ID
		WriteRawToFile(file, Name->Length);	//NameLength
		for each (char c in Name) {
			WriteRawToFile(file, c); //Name
		}
		WriteRawToFile(file, BoneCount);
		m_skeleton->WriteToFile(file);
	}

	void Skeleton::ExportToFile() {
		throw gcnew System::NotImplementedException();
	}

	Skeleton^ Skeleton::FromFile(System::String^ path) {
		std::ifstream file(ConvertString(path), std::ios::in | std::ios::binary);
		if (!file.is_open()) {
			throw gcnew System::IO::IOException(ConvertString("Failed to open skeleton file: " + std::string(strerror(errno))));
		}

		byte type = ReadRawFromFile<byte>(file); //File type
		bool isDesignerFile = false;
		if (type == 5) isDesignerFile = true;
		else if (type != 3) throw gcnew System::ArgumentException("File is not a skeleton file!");

		unsigned int resourceId = ReadRawFromFile<unsigned int>(file); //Resource ID
		std::string name = "Unknown";
		if (isDesignerFile)
			name = ReadRawFromFile<std::string>(file);	//Name
		unsigned int boneCount = ReadRawFromFile<unsigned int>(file); //Bone Count

		auto skeleton = InternSkeleton::FromFile(file, boneCount);

		return gcnew Skeleton(ConvertString(name), path, skeleton);
	}
}