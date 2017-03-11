#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Model {
	protected:
		std::vector<const Material*> m_materials;
		const Mesh* m_mesh;
		bool m_isAnimated;
		Model(const Mesh* mesh, std::vector<const Material*>& materials, bool isAnimated);
	public:
		Model(const Mesh* mesh, std::vector<const Material*>& materials);

		const std::vector<const Material*>& GetMaterials() const { return m_materials; }
		std::vector<const Material*>& GetMaterials() { return m_materials; }
		const Mesh* const& GetMesh() const { return m_mesh; }
		bool IsAnimated() const { return m_isAnimated; }
	};

	class ENGINE_DLL AnimatedModel : public Model {
	private:
		const Animation* m_animation;

		double m_animationTime;
	public:
		AnimatedModel(const Mesh* mesh, std::vector<const Material*>& materials, const Animation* animation, double animationStartTime = 0.0);

		const Animation* GetAnimation() const { return m_animation; }
		double GetAnimationTime() const { return m_animationTime; }

		void SetAnimation(const Animation* animation) { m_animation = animation; }
		void SetAnimationTime(double time) { m_animationTime = time; }
		void AddToAnimationTime(double time) { m_animationTime += time; }
	};
}