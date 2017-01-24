#include <Engine.h>

namespace FM3D {

	std::mutex Output::s_mutex;
	std::vector<std::vector<uint>> Output::s_targets;
	std::vector<std::vector<uint>> Output::s_options;
	std::function<void(uint type, uint level, uint target, uint option, std::string file, uint line, std::string message, std::string information)> Output::s_handler;
	bool Output::s_enabled = true;

	void Output::Initialize() {
		s_options.reserve(OUTPUT_TYPE_COUNT);
		for(uint i = 0; i < OUTPUT_TYPE_COUNT; i++)
			s_options.push_back(std::vector<uint>(OUTPUT_LEVEL_MAX + 1));

		s_targets.reserve(OUTPUT_TYPE_COUNT);
		for (uint i = 0; i < OUTPUT_TYPE_COUNT; i++)
			s_targets.push_back(std::vector<uint>(OUTPUT_LEVEL_MAX + 1));

		s_handler = &Output::Handle;
	}

	void Output::SetTargetForAll(uint target) {
		for (uint i = 0; i < OUTPUT_TYPE_COUNT; i++) {
			for (uint j = 0; j < OUTPUT_LEVEL_MAX; j++)
				SetTarget(target, i, j);
		}
	}

	void Output::SetTarget(uint target, uint type, uint level) {
		std::lock_guard<std::mutex> lock(s_mutex);
		s_targets[type][level] = target;
	}

	void Output::SetTarget(uint target, uint type, uint level, bool lowerLevels, bool higherLevels) {
		SetTarget(target, type, level);
		if (lowerLevels) {
			for (size_t i = level - 1; i >= 0; i--)
				SetTarget(target, type, i);
		}
		if (higherLevels) {
			for (size_t i = OUTPUT_LEVEL_MAX; i > level; i--)
				SetTarget(target, type, i);
		}
	}

	void Output::SetOptionToAll(uint option) {
		SetOptionToType(option, OUTPUT_TYPE_INFO);
		SetOptionToType(option, OUTPUT_TYPE_WARNING);
		SetOptionToType(option, OUTPUT_TYPE_ERROR);
		SetOptionToType(option, OUTPUT_TYPE_FATAL);
	}

	void Output::SetOptionToType(uint option, uint type) {
		for (size_t i = 0; i <= OUTPUT_LEVEL_MAX; i++)
			SetOptionToType(option, type, i);
	}

	void Output::SetOptionToType(uint option, uint type, uint level) {
		std::lock_guard<std::mutex> lock(s_mutex);
		s_options[type][level] = option;
	}

	void Output::SetOptionToType(uint option, uint type, uint level, bool lowerLevels, bool higherLevels) {
		SetOptionToType(option, type, level);
		if (lowerLevels) {
			for (size_t i = level - 1; i >= 0; i--)
				SetOptionToType(option, type, i);
		}
		if (higherLevels) {
			for (size_t i = OUTPUT_LEVEL_MAX; i > level; i--)
				SetOptionToType(option, type, i);
		}
	}

	void Output::Out(uint type, uint level, std::string file, uint line, std::string message, std::string information) {
		std::lock_guard<std::mutex> lock(s_mutex);
		if(s_enabled)
			s_handler(type, level, s_targets[type][level], s_options[type][level], file, line, message, information);
	}

	void Output::Enable() {
		std::lock_guard<std::mutex> lock(s_mutex);
		s_enabled = true;
	}

	bool Output::IsEnabled() {
		std::lock_guard<std::mutex> lock(s_mutex);
		return s_enabled;
	}

	void Output::Disable() {
		std::lock_guard<std::mutex> lock(s_mutex);
		s_enabled = false;
	}

	void Output::Reset() {
		s_targets.clear();
		s_options.clear();
		s_handler = NULL;
		s_enabled = true;
		Initialize();
	}

	void Output::Handle(uint type, uint level, uint target, uint option, std::string file, uint line, std::string message, std::string information) {
		if ((target & OUTPUT_TARGET_CONSOLE) != 0 || (target & OUTPUT_TARGET_DEBUG) != 0) {
			std::stringstream s;
			switch (type) {
			case OUTPUT_TYPE_INFO:
				s << "[INFO "<<  level << "] ";
				break;
			case OUTPUT_TYPE_ERROR:
				s << "[ERROR " << level << "] ";
				break;
			case OUTPUT_TYPE_WARNING:
				s << "[WARNING " << level << "] ";
				break;
			case OUTPUT_TYPE_FATAL:
				s << "[FATAL ERROR " << level << "] ";
				break;
			}
			if ((option & OUTPUT_OPTION_TIME) != 0) {
				s << "[" << Timer::GetCurrentTimeString("%T") << "] ";
			}
			if ((option & OUTPUT_OPTION_LINE) != 0) {
				s << "[In " << file << " " << line << "] ";
			}
			std::string str = s.str();
			str.pop_back();
			str += ": " + message;
			if ((option & OUTPUT_OPTION_INFORMATION) != 0) {
				str += ": " + information;
			}

			if ((target & OUTPUT_TARGET_CONSOLE) != 0) {
					std::cout << str << std::endl;
			}
			if ((target & OUTPUT_TARGET_DEBUG) != 0) {
				OutputDebugStringA((str + '\n').c_str());
			}
		}
		if ((target & OUTPUT_TARGET_MESSAGEBOX) != 0) {
			std::string caption;
			std::string text;
			switch (type) {
			case OUTPUT_TYPE_INFO:
				caption = "INFO";
				break;
			case OUTPUT_TYPE_ERROR:
				caption = "WARNING";
				break;
			case OUTPUT_TYPE_WARNING:
				caption = "ERROR";
				break;
			case OUTPUT_TYPE_FATAL:
				caption = "FATAL ERROR";
				break;
			}
			caption += (" " + std::to_string(level));

			text = message + '\n' + file + " " + std::to_string(line);
			if ((option & OUTPUT_OPTION_LINE) != 0) {
				text += ("\n\n" + information);
			}

#ifdef _WIN32
			MessageBoxA(NULL, text.c_str(), caption.c_str(), MB_OK);
#else
			static_assert(false, "Linux Messagebox not implemented!");
#endif
		}
		if ((option & OUTPUT_OPTION_BREAK) != 0) {
			__debugbreak();
		}
		if ((option & OUTPUT_OPTION_EXIT) != 0) {
			exit(1);
		}
	}

}