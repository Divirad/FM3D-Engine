#include "FoundResource.h"
#include "../pch.h"

namespace DesignerLib {

	FoundResource::FoundResource(std::string name, std::string path, Type^ type) {
		this->Name = ConvertString(name);
		this->Path = ConvertString(path);
		this->ResType = type;
		this->Content = gcnew ObservableCollection<FoundResource^>();
		this->IsReference = false;
	}
	FoundResource::FoundResource(FoundResource^ parent, FoundResource^ reference) {
		this->Name = reference->Name;
		this->Path = "";
		this->ResType = reference->ResType;
		this->Content = nullptr;
		this->IsReference = true;
	}


	FoundResource::FoundResource() {
		this->Name = "Null-Name";
		this->Path = "Null-Path";
		this->ResType = Type::Unknown;
		this->Content = gcnew ObservableCollection<FoundResource^>();
		this->IsReference = false;
	}
}