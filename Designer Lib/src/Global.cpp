#include "Global.h"
#include <Engine.h>

bool Global::init = false;

using namespace FM3D;

void Global::Init() {
	if (!init) {
		Output::Initialize();
		Output::SetTargetForAll(OUTPUT_TARGET_CONSOLE | OUTPUT_TARGET_DEBUG);
		Output::SetOptionToAll(OUTPUT_OPTION_INFORMATION | OUTPUT_OPTION_LINE | OUTPUT_OPTION_TIME);

		FileManager::Initialize("res/", "../../../FM3D-Engine/", "fm3d");
		ExternFileManager::Initialize();
	}
}