#include <Engine.h>

namespace FM3D {
	Material::Material(uint color, const Texture * texture, float specular, const Texture * specularMap, const Texture * normalMap, bool useWireframe):
	color(color), texture(texture), specularFactor(specular), specularMap(specularMap), normalMap(normalMap), useWireframe(useWireframe) {
	}

	Material::Material(uint color, const Texture* texture, const Texture* normalMap, bool useWireframe):
	Material(color, texture, 1.0f, nullptr, normalMap, useWireframe) {
	}

	Material::Material(uint color, const Texture * texture, bool useWireframe):
	Material(color, texture, nullptr, useWireframe) {
	}

	Material::Material(uint color, bool useWireframe):
	Material(color, nullptr, nullptr, useWireframe) {
	}
}