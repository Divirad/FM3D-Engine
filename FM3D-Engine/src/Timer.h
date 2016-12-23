#pragma once
#include <Engine.h>

namespace FM3D {

	class Timer {
	public:
		static std::string GetCurrentTimeString(char* format);
		static std::string GetTimeString(time_t* t, char* format);
	};
}