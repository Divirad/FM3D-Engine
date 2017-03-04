#pragma once
#include <Engine.h>

namespace FM3D {

	struct ENGINE_DLL Material {
		uint color;
		const Texture* texture;
		const Texture* normalMap;
		bool useWireframe;
		float specularFactor;
		const Texture* specularMap;

		Material(uint color = 0xffffffff, const Texture* texture = nullptr, float specular = 0.04f, const Texture* specularMap = nullptr, const Texture* normalMap = nullptr, bool useWireframe = false);
		Material(uint color, const Texture* texture, const Texture* normalMap, bool useWireframe = false);
		Material(uint color, const Texture* texture, bool useWireframe);
		Material(uint color, bool useWireframe);
	};
}