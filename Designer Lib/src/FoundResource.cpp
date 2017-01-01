#include "FoundResource.h"

namespace DesignerLib {

	FoundResource::FoundResource(std::string name, std::string path, Type^ type) {
		this->Selected = true;
		this->Name = ConvertString(name);
		this->Path = ConvertString(path);
		this->ResType = type;
		this->References = gcnew ObservableCollection<ResourceReference^>();
	}

	FoundResource::FoundResource() {
		this->Selected = true;
		this->Name = "Null-Name";
		this->Path = "Null-Path";
		this->ResType = Type::Unknown;
		this->References = gcnew ObservableCollection<ResourceReference^>();
	}

	ResourceReference::ResourceReference(FoundResource^ parent, FoundResource^ ref) {
		this->Parent = parent;
		this->Reference = ref;
		this->Active = true;
	}
}