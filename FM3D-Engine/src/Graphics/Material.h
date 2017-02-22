#pragma once
#include <Engine.h>

namespace FM3D {

	struct Material {
		uint color;
		const Texture* texture;
		const Texture* normalMap;
	};
}