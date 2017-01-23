#pragma once

#include <msclr\marshal_cppstd.h>

namespace DesignerLib {
	using uint = unsigned int;
	using byte = unsigned char;

	inline System::String^ ConvertString(const std::string& str) {
		return msclr::interop::marshal_as<System::String^>(str);
	}

	inline std::string ConvertString(System::String^ str) {
		return msclr::interop::marshal_as<std::string>(str);
	}
}