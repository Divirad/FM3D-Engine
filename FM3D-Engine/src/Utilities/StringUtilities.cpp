#include <Engine.h>

namespace ENGINE_NAME {

	std::string StringUtilities::RemoveSpacesAtFrontAndBack(const std::string& string) {
		uint i;
		for (i = 0u; i < string.length() && string[i] == ' '; i++);
		int j;
		for (j = (int)string.length()-1; j >= 0 && string[j] == ' '; j--);
		return string.substr(i, j - i + 1);
	}

	std::string StringUtilities::ComplicatedString(const std::string& string, const std::vector<Define>& defines, const std::vector<std::string>& extraParts) {
		return StringWithParts(StringWithDefines(string, defines), extraParts);
	}

	struct DefinePosition {
		const StringUtilities::Define d;
		uint pos;
	};

	std::string StringUtilities::StringWithDefines(const std::string& string, const std::vector<Define>& defines) {
		static const std::string DEFINE = "DEFINE_";
		int d = 0;
		std::list<Define> possibleDefines;
		std::vector<DefinePosition> foundDefines;
		std::string result = "";
		uint startPos = 0u;
		uint i;

		//Find Defines
		for (i = 0u; i < string.length(); i++) {
			if (string[i] == DEFINE[d]) {
				d++;
				if (d == DEFINE.length()) {
					d = 0;
					for (const Define& define : defines) {
						if (define.define[0] == string[i + 1]) possibleDefines.push_front(define);
					}
					for (uint x = 2; !possibleDefines.empty(); x++) {
						for (std::list<Define>::iterator it = possibleDefines.begin(); it != possibleDefines.end(); ++it) {
							if ((*it).define[x-1] != string[i+x]) {
								possibleDefines.erase(it);
								if (possibleDefines.empty()) break;
								if(it != possibleDefines.begin())--it;
							} else {
								if ((*it).define.length() == x + 1) {
									foundDefines.push_back({ *it , i - DEFINE.length() + 1});
									possibleDefines.clear();
									break;
								}
							}
						}
					}
				}
			} else {
				d = 0;
			}
		}

		//Replace Defines
		d = 0;
		for (i = 0u; i < string.length() && d < (int) foundDefines.size(); i++) {
			if (i == foundDefines[d].pos) {
				result += foundDefines[d].d.value;
				i += DEFINE.length() + foundDefines[d].d.define.length() - 1;
				d++;
			} else {
				result += string[i];
			}
		}
		for (; i < string.length(); i++) result += string[i];
		return result;
	}

	std::string StringUtilities::StringWithParts(const std::string& string, const std::vector<std::string>& extraParts) {
		static const std::string ONLY = "ONLY_";
		static const std::string NOT = "NOT_";
		uint o = 0u, n = 0u;
		std::string result = "";

		for (uint i = 0u; i < string.length(); i++) {
			if (string[i] == ONLY[o]) {
				o++;
				if (o == ONLY.length()) {
					uint begin = i - ONLY.length() + 1;
					uint endOnly = i;
					while (string[i++] != '{');
					uint start = i;
					for (uint bracket = 1u; bracket != 0u; i++) {
						if (i == string.length()) throw new std::exception("Only section doesn't close");
						if (string[i] == '{') {
							bracket++;
						} else if (string[i] == '}') {
							bracket--;
						}
					}
					std::string name = RemoveSpacesAtFrontAndBack(string.substr(endOnly + 1, start - endOnly - 2));
					return StringWithParts(string.substr(0, begin) + (StringVectorContains(extraParts, name) ? string.substr(start, i-start-1) : "") + string.substr(i), extraParts);
				}
			} else {
				o = 0u;
			}
			if (string[i] == NOT[n]) {
				n++;
				if (n == NOT.length()) {
					uint begin = i - NOT.length() + 1;
					uint endNot = i;
					while (string[i++] != '{');
					uint start = i;
					for (uint bracket = 1u; bracket != 0u; i++) {
						if (i == string.length()) throw new std::exception("Not section doesn't close");
						if (string[i] == '{') {
							bracket++;
						} else if (string[i] == '}') {
							bracket--;
						}
					}
					std::string name = RemoveSpacesAtFrontAndBack(string.substr(endNot + 1, start - endNot - 2));
					return StringWithParts(string.substr(0, begin) + (StringVectorContains(extraParts, name) ? "" : string.substr(start, i - start - 1)) + string.substr(i), extraParts);
				}
			} else {
				n = 0u;
			}
		}
		return string;
	}
	
	bool StringUtilities::StringVectorContains(const std::vector<std::string>& vec, std::string& str) {
		for (const std::string& s : vec) {
			if (s.compare(str) == 0) return true;
		}
		return false;
	}
}
