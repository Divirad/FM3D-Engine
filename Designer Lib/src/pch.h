#pragma once

#include <Engine.h>
#include <msclr\marshal_cppstd.h>

namespace DesignerLib {
	using uint = FM3D::uint;
	using byte = FM3D::byte;

	inline System::String^ ConvertString(const std::string& str) {
		return msclr::interop::marshal_as<System::String^>(str);
	}

	inline std::string ConvertString(System::String^ str) {
		return msclr::interop::marshal_as<std::string>(str);
	}
}