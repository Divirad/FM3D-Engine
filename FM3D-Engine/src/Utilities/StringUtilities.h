#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL StringUtilities {
	public:
		struct Define {
			std::string define;
			std::string value;
		};

		static inline std::string ComplicatedString(const std::string& string, const std::vector<Define>& defines, const std::vector<std::string>& extraParts);
		static std::string StringWithDefines(const std::string& string, const std::vector<Define>& defines);
		static std::string StringWithParts(const std::string& string, const std::vector<std::string>& extraParts);

		static bool StringVectorContains(const std::vector<std::string> &vec, std::string& str);

		static std::string RemoveSpacesAtFrontAndBack(const std::string& string);
	};
}