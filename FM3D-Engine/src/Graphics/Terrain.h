#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Terrain {
	private:
		Vector3f m_position;
		Vector3f m_rotation;
		Vector3f m_scale;

		const Mesh* m_mesh;
		const Texture* m_spatmap;
		const Texture* m_normalmap;
		std::vector<std::pair<Texture*, float>> m_materials;

		float m_texCount;
	public:
		Terrain(const Mesh* mesh, const Texture* spatmap, const Texture* normalmap, std::vector<std::pair<Texture*, float>>&& materials, float texCount);

		inline const Vector3f& GetPosition() const { return m_position; }
		inline void SetPosition(const Vector3f& position) { m_position = position; }
		inline const Vector3f& GetRotation() const { return m_rotation; }
		inline void SetRotation(const Vector3f& rotation) { m_rotation = rotation; }
		inline const Vector3f& GetScale() const { return m_scale; }
		inline void SetScale(const Vector3f& scale) { m_scale = scale; }

		inline const Mesh* GetMesh() const { return m_mesh; };
		inline const Texture* GetSpatmap() const { return m_spatmap; }
		inline const Texture* GetNormalmap() const { return m_normalmap; }
		inline const std::vector<std::pair<Texture*, float>>& GetMaterials() const { return m_materials; }

		inline float GetTexCount() const { return m_texCount; }

		inline Matrix4f GetMatrix() const {
			return Matrix4f::Transformation(m_position, m_scale, m_rotation);
		}
	};

}