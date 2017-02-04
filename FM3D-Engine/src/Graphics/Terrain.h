#pragma once
#include <Engine.h>

namespace FM3D {

	class Terrain {
	private:
		std::map<Vector2i, std::vector<std::vector<float>>> m_heights;
		Vector2f m_size;
		Vector2i m_partCount;
		Vector2i m_partSize;
		Vector2f m_triangleSize;
	public:
		Terrain(Texture* heightMap, Vector2f size, Vector2i partCount, Vector2i partSize,
			Texture* colorMap, Texture* tex0, Texture* tex1, Texture* tex2, Texture* tex3);
	};

}