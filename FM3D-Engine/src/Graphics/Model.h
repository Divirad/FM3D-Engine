#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Model {
	protected:
		Array<const Material*> m_materials;
		const Mesh* m_mesh;
		bool m_isAnimated;
		Model(const Mesh* mesh, RawArray<const Material*>& materials, bool isAnimated);
	public:
		Model(const Mesh* mesh, RawArray<const Material*>& materials);

		const Array<const Material*>& GetMaterials() const { return m_materials; }
		Array<const Material*>& GetMaterials() { return m_materials; }
		const Mesh* const& GetMesh() const { return m_mesh; }
		bool IsAnimated() const { return m_isAnimated; }
	};

	class AnimatedModel : public Model {
	private:
		const Animation* m_animation;

		double m_animationTime;
	public:
		AnimatedModel(const Mesh* mesh, RawArray<const Material*>& materials, const Animation* animation, double animationStartTime = 0.0);

		double& GetAnimationTime() { return m_animationTime; }
		const double& GetAnimationTime() const { return m_animationTime; }

		const Animation* GetAnimation() const { return m_animation; }
	};
}