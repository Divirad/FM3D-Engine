#include <Engine.h>
#include "MeshCreator.h"

namespace FM3D {

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

		return renderSystem->CreateMesh(nullptr, false, std::vector<MeshPart>({ { 60, (void*)indices, std::move(vertices), sizeof(byte), false } }));
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

		return renderSystem->CreateMesh(nullptr, false, std::vector<MeshPart>({ { 6, (void*)indices, std::move(vertices), sizeof(byte), false } }));
	}

	static void SetTex(Vertices& vertices) {
		vertices.GetTexCoord(0) = Vector2f(0.0f, 0.0f);
		vertices.GetTexCoord(1) = Vector2f(1.0f, 0.0f);
		vertices.GetTexCoord(2) = Vector2f(1.0f, 1.0f);
		vertices.GetTexCoord(3) = Vector2f(0.0f, 1.0f);

		vertices.GetNormal(0) = Vector3f(0.0f, 0.0f, 0.0f);
		vertices.GetNormal(1) = Vector3f(0.0f, 0.0f, 0.0f);
		vertices.GetNormal(2) = Vector3f(0.0f, 0.0f, 0.0f);
		vertices.GetNormal(3) = Vector3f(0.0f, 0.0f, 0.0f);
	}

	Mesh * MeshCreator::CreateCube(const RenderSystem * renderSystem, Vector3f pos, float size) {
		const auto x = Vector3f::XAxis() * size;
		const auto y = Vector3f::XAxis() * size;
		const auto z = Vector3f::XAxis() * size;
		byte indices[] = { 0, 1, 2, 2, 3, 0 };
		std::vector<MeshPart> parts;
		parts.reserve(6);

		Vertices vertices0(4, Vertices::POSITION | Vertices::NORMAL | Vertices::TEXCOORD);
		Vertices vertices1(4, Vertices::POSITION | Vertices::NORMAL | Vertices::TEXCOORD);
		Vertices vertices2(4, Vertices::POSITION | Vertices::NORMAL | Vertices::TEXCOORD);
		Vertices vertices3(4, Vertices::POSITION | Vertices::NORMAL | Vertices::TEXCOORD);
		Vertices vertices4(4, Vertices::POSITION | Vertices::NORMAL | Vertices::TEXCOORD);
		Vertices vertices5(4, Vertices::POSITION | Vertices::NORMAL | Vertices::TEXCOORD);

		//vertices0.SetPosition(Vector3f(-1.0f, -1.0f, 1.0f), 0);
		//vertices0.SetPosition(Vector3f(1.0f, -1.0f, 1.0f), 0);
		//vertices0.SetPosition(Vector3f(1.0f, 1.0f, 1.0f), 0);
		//vertices0.SetPosition(Vector3f(-1.0f, 1.0f, 1.0f), 0);

		//vertices.SetPosition(Vector3f(-1.0f, -1.0f, -1.0f), 0);
		//vertices.SetPosition(Vector3f(1.0f, -1.0f, -1.0f), 0);
		//vertices.SetPosition(Vector3f(1.0f, 1.0f, -1.0f), 0);
		//vertices.SetPosition(Vector3f(-1.0f, 1.0f, -1.0f), 0);



		vertices0.SetPosition(Vector3f(-1.0f, -1.0f, 1.0f), 0);
		vertices0.SetPosition(Vector3f(1.0f, -1.0f, 1.0f), 1);
		vertices0.SetPosition(Vector3f(1.0f, 1.0f, 1.0f), 2);
		vertices0.SetPosition(Vector3f(-1.0f, 1.0f, 1.0f), 3);
		SetTex(vertices0);
		parts.push_back({ 6, (void*)indices, std::move(vertices0), sizeof(byte), false });

		vertices1.SetPosition(Vector3f(1.0f, -1.0f, 1.0f), 0);
		vertices1.SetPosition(Vector3f(1.0f, -1.0f, -1.0f), 1);
		vertices1.SetPosition(Vector3f(1.0f, 1.0f, -1.0f), 2);
		vertices1.SetPosition(Vector3f(1.0f, 1.0f, 1.0f), 3);
		SetTex(vertices1);
		parts.push_back({ 6, (void*)indices, std::move(vertices1), sizeof(byte), false });

		vertices2.SetPosition(Vector3f(1.0f, -1.0f, -1.0f), 0);
		vertices2.SetPosition(Vector3f(-1.0f, -1.0f, -1.0f), 1);
		vertices2.SetPosition(Vector3f(-1.0f, 1.0f, -1.0f), 2);
		vertices2.SetPosition(Vector3f(1.0f, 1.0f, -1.0f), 3);
		SetTex(vertices2);
		parts.push_back({ 6, (void*)indices, std::move(vertices2), sizeof(byte), false });

		vertices3.SetPosition(Vector3f(-1.0f, -1.0f, -1.0f), 0);
		vertices3.SetPosition(Vector3f(-1.0f, -1.0f, 1.0f), 1);
		vertices3.SetPosition(Vector3f(-1.0f, 1.0f, 1.0f), 2);
		vertices3.SetPosition(Vector3f(-1.0f, 1.0f, -1.0f), 3);
		SetTex(vertices3);
		parts.push_back({ 6, (void*)indices, std::move(vertices3), sizeof(byte), false });

		vertices4.SetPosition(Vector3f(-1.0f, -1.0f, 1.0f), 0);
		vertices4.SetPosition(Vector3f(-1.0f, -1.0f, -1.0f), 1);
		vertices4.SetPosition(Vector3f(1.0f, -1.0f, -1.0f), 2);
		vertices4.SetPosition(Vector3f(1.0f, -1.0f, 1.0f), 3);
		SetTex(vertices4);
		parts.push_back({ 6, (void*)indices, std::move(vertices4), sizeof(byte), false });

		vertices5.SetPosition(Vector3f(1.0f, 1.0f, 1.0f), 0);
		vertices5.SetPosition(Vector3f(1.0f, 1.0f, -1.0f), 1);
		vertices5.SetPosition(Vector3f(-1.0f, 1.0f, -1.0f), 2);
		vertices5.SetPosition(Vector3f(-1.0f, 1.0f, 1.0f), 3);
		SetTex(vertices5);
		parts.push_back({ 6, (void*)indices, std::move(vertices5), sizeof(byte), false });

		return renderSystem->CreateMesh(nullptr, false, parts);
	}

}