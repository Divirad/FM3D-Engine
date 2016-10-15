#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL Model {
	protected:
		Array<const Material*> m_materials;
		const Mesh* m_mesh;
	public:	
		Model(const Mesh* mesh, SharedArray<const Material*>& materials);

		const Array<const Material*>& GetMaterials() const { return m_materials; }
		Array<const Material*>& GetMaterials() { return m_materials; }
		const Mesh* const& GetMesh() const { return m_mesh; }
	};

	class AnimatedModel : public Model {
	private:
		
		const Animation* m_animation;

		double m_animationTime;
	};
}