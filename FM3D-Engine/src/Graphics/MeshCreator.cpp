#include <Engine.h>
#include "MeshCreator.h"

namespace ENGINE_NAME {

	Mesh * MeshCreator::CreateIcosahedron(const RenderSystem* renderSystem) {
		const float t = (1.0f + std::sqrt(5.0f)) / 2.0f;

		Vertices vertices(12, Vertices::POSITION);
		vertices.GetPosition(0) = Vector3f(-1.0f, t, 0.0f).Normalize();
		vertices.GetPosition(1) = Vector3f(1.0f, t, 0.0f).Normalize();
		vertices.GetPosition(2) = Vector3f(-1.0f, -t, 0.0f).Normalize();
		vertices.GetPosition(3) = Vector3f(1.0f, -t, 0.0f).Normalize();
		vertices.GetPosition(4) = Vector3f(0.0f, -1.0f, t).Normalize();
		vertices.GetPosition(5) = Vector3f(0.0f, 1.0f, t).Normalize();
		vertices.GetPosition(6) = Vector3f(0.0f, -1.0f, -t).Normalize();
		vertices.GetPosition(7) = Vector3f(0.0f, 1.0f, -t).Normalize();
		vertices.GetPosition(8) = Vector3f(t, 0.0f, -1.0f).Normalize();
		vertices.GetPosition(9) = Vector3f(t, 0.0f, 1.0f).Normalize();
		vertices.GetPosition(10) = Vector3f(-t, 0.0f, -1.0f).Normalize();
		vertices.GetPosition(11) = Vector3f(-t, 0.0f, 1.0f).Normalize();

		byte indices[] = { 0, 11, 5,0, 5, 1, 0, 1, 7, 0, 7, 10, 0, 10, 11, 1, 5, 9, 5, 11, 4, 11, 10, 2, 10, 7, 6, 7, 1, 8, 3, 9, 4, 3, 4, 2, 3, 2, 6, 3, 6, 8, 3, 8, 9, 4, 9, 5, 2, 4, 11, 6, 2, 10, 8, 6, 7, 9, 8, 1 };
	
		return renderSystem->CreateMesh(nullptr, false, SharedArray<Mesh::Part>({ { 60, (void*)indices, vertices, sizeof(byte), false } }));
	}

	Mesh * MeshCreator::CreateRectangle(const RenderSystem* renderSystem, Vector3f pos, Vector2f size) {
		byte indices[] = { 0, 1, 2, 2, 3, 0 };
		Vertices vertices(4, Vertices::POSITION | Vertices::TEXCOORD);

		vertices.GetPosition(0) = pos;
		vertices.GetTexCoord(0) = Vector2f(0.0f, 0.0f);
		vertices.GetPosition(1) = Vector3f(pos.x, pos.y + size.y, pos.z);
		vertices.GetTexCoord(1) = Vector2f(0.0f, 1.0f);
		vertices.GetPosition(2) = Vector3f(pos.x + size.x, pos.y + size.y, pos.z);
		vertices.GetTexCoord(2) = Vector2f(1.0f, 1.0f);
		vertices.GetPosition(3) = Vector3f(pos.x + size.x, pos.y, pos.z);
		vertices.GetTexCoord(3) = Vector2f(1.0f, 0.0f);

		return renderSystem->CreateMesh(nullptr, false, SharedArray<Mesh::Part>({ { 6, (void*)indices, vertices, sizeof(byte), false } }));
	}

}