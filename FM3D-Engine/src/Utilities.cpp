#include <Engine.h>

using namespace std;

namespace ENGINE_NAME {

	uint Utilities::GetStringLength(const char* string) {
		for (uint i = 0; i < 0xffffffff; i++) {
			if (string[i] == '\0') return i;
		}
		std::cout << "Can't get stringlength! String is not Null-terminated!" << std::endl;
		return 0u;
	}

	string Utilities::StringWithDefines(string str, string define, uint definedNumber) {
		return StringWithDefines(str, define, to_string(definedNumber));
	}

	string Utilities::StringWithDefines(string str, string define, string definedString) {
		string result = "";
		for (uint i = 0, d = 0; i < str.length(); i++) {
			char c = str[i];
			if (str[i] != define[d]) {
				for (uint x = i - d; x <= i; x++) {
					result += str[x];
				}
				d = 0;
			} else {
				d++;
				if (d == define.length()) {
					for (uint x = 0; x < definedString.length(); x++) {
						result += definedString[x];
					}
					d = 0;
				}
			}
		}

		return result;
	}
}