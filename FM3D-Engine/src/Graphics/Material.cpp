#include <Engine.h>

namespace FM3D {

	Material::Material(uint color, const Texture* texture, const Texture* normalMap, bool useWireframe):
	color(color), texture(texture), normalMap(normalMap), useWireframe(useWireframe) {
	}

	Material::Material(uint color, const Texture * texture, bool useWireframe):
	Material(color, texture, nullptr, useWireframe) {
	}

	Material::Material(uint color, bool useWireframe):
	Material(color, nullptr, nullptr, useWireframe) {
	}
}