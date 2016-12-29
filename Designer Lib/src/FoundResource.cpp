#include "FoundResource.h"

namespace DesignerLib {

	FoundResource::FoundResource(std::string name) {
		this->Selected = true;
		this->Name = ConvertString(name);
		this-> Path = "Not implemented yet: Path";
	}

	FoundResource::FoundResource() {
		this->Selected = true;
		this->Name = "Null-Name";
		this->Path = "Null-Path";
	}
}