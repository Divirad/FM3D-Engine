#include <Engine.h>
#include "Timer.h"

namespace FM3D {

	std::string Timer::GetCurrentTimeString(char* format) {
		time_t t = time(nullptr);
		return GetTimeString(&t, format);
	}

	std::string Timer::GetTimeString(time_t* t, char* format) {
		char c_str[50];
		tm tm;
		localtime_s(&tm, t);
		strftime(c_str, 50, "%T", &tm);
		return c_str;
	}

}
