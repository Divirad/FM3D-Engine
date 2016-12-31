#pragma once
#include"pch.h"

namespace DesignerLib {

	public ref class FoundResource {
	public:
		property bool Selected;
		property System::String^ Name;
		property System::String^ Path;

		FoundResource(std::string name);

		FoundResource();
	};
}