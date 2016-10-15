#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL MeshCreator {
	public:
		static Mesh* CreateIcosahedron(const RenderSystem* renderSystem);
		static Mesh* CreateRectangle(const RenderSystem* renderSystem, Vector3f pos, Vector2f size);
	};
}