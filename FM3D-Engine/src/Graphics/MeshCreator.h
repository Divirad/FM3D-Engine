#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL MeshCreator {
	public:
		static Mesh* CreateIcosahedron(const RenderSystem* renderSystem);
		static Mesh* CreateRectangle(const RenderSystem* renderSystem, Vector3f pos, Vector2f size);
		static Mesh* CreateCube(const RenderSystem* renderSystem, Vector3f pos, float size);
	};
}