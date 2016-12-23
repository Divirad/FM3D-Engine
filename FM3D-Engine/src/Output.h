#pragma once
#include <Engine.h>

#define OUTPUT_TYPE_INFO				0x00U
#define OUTPUT_TYPE_WARNING				0x01U
#define OUTPUT_TYPE_ERROR				0x02U
#define OUTPUT_TYPE_FATAL				0x03U
#define OUTPUT_TYPE_COUNT				0x04U

#define OUTPUT_TARGET_INACTIVE			0x00U
#define OUTPUT_TARGET_CONSOLE			0x01U
#define OUTPUT_TARGET_MESSAGEBOX		0x02U
#define OUTPUT_TARGET_DEBUG				0x04U

#define OUTPUT_OPTION_NONE				0x00U
#define OUTPUT_OPTION_INFORMATION		0x01U
#define OUTPUT_OPTION_BREAK				0x02U
#define OUTPUT_OPTION_EXIT				0x04U
#define OUTPUT_OPTION_LINE				0x08U
#define OUTPUT_OPTION_TIME				0x10U

#define OUTPUT_LEVEL_0					0x00U
#define OUTPUT_LEVEL_1					0x01U
#define OUTPUT_LEVEL_2					0x02U
#define OUTPUT_LEVEL_3					0x03U
#define OUTPUT_LEVEL_4					0x04U
#define OUTPUT_LEVEL_5					0x05U
#define OUTPUT_LEVEL_6					0x06U
#define OUTPUT_LEVEL_7					0x07U
#define OUTPUT_LEVEL_8					0x08U
#define OUTPUT_LEVEL_9					0x09U
#define OUTPUT_LEVEL_10					0x0AU
#define OUTPUT_LEVEL_11					0x0BU
#define OUTPUT_LEVEL_12					0x0CU
#define OUTPUT_LEVEL_13					0x0DU
#define OUTPUT_LEVEL_14					0x0EU
#define OUTPUT_LEVEL_15					0x0FU
#define OUTPUT_LEVEL_MAX				0x0FU

#define OUTPUT_INFO(level, message, information) Output::Out(OUTPUT_TYPE_INFO, level, __FILE__, __LINE__, message, information)
#define OUTPUT_WARNING(level, message, information) Output::Out(OUTPUT_TYPE_WARNING, level, __FILE__, __LINE__, message, information)
#define OUTPUT_ERROR(level, message, information) Output::Out(OUTPUT_TYPE_ERROR, level, __FILE__, __LINE__, message, information)
#define OUTPUT_FATAL(level, message, information) Output::Fatal(OUTPUT_TYPE_FATAL, level, __FILE__, __LINE__, message, information)

namespace FM3D {

	class ENGINE_DLL Output {
	private:
		static std::mutex s_mutex;
		static std::vector<std::vector<uint>> s_targets;
		static std::vector<std::vector<uint>> s_options;
		static std::function<void(uint type, uint level, uint target, uint option, std::string file, uint line, std::string message, std::string information)> s_handler;
		static bool s_enabled;
	public:
		static void Initialize();

		static void SetTargetForAll(uint target);
		static void SetTarget(uint target, uint type, uint level);
		static void SetTarget(uint target, uint type, uint level, bool lowerLevels, bool higherLevels);
		static void SetOptionToAll(uint option);
		static void SetOptionToType(uint option, uint type);
		static void SetOptionToType(uint option, uint type, uint level);
		static void SetOptionToType(uint option, uint type, uint level, bool lowerLevels, bool higherLevels);

		static void Out(uint type, uint level, std::string file, uint line, std::string message, std::string information);

		static void Enable();
		static bool IsEnabled();
		static void Disable();
		static void Reset();
	private:
		static void Handle(uint type, uint level, uint target, uint option, std::string file, uint line, std::string message, std::string information);
	};

}