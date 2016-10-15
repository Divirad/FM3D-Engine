#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Utilities {
	public:
		static uint GetStringLength(const char* string);
		static std::string StringWithDefines(std::string str, std::string define, uint definedNumber);
		static std::string StringWithDefines(std::string str, std::string define, std::string definedString);
	};
}