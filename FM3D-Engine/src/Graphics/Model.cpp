#include <Engine.h>

namespace FM3D {

	Model::Model(const Mesh* mesh, RawArray<const Material*>& materials, bool isAnimated)
		: m_mesh(mesh), m_materials(materials), m_isAnimated(isAnimated) {

	}

	Model::Model(const Mesh* mesh, RawArray<const Material*>& materials)
		: m_mesh(mesh), m_materials(materials), m_isAnimated(false) {

	}

	AnimatedModel::AnimatedModel(const Mesh* mesh, RawArray<const Material*>& materials, const Animation* animation, double animationStartTime)
		: Model(mesh, materials, true), m_animation(animation), m_animationTime(animationStartTime) {

	}

}