#include <Engine.h>

namespace ENGINE_NAME {

	Model::Model(const Mesh* mesh, SharedArray<const Material*>& materials): m_mesh(mesh), m_materials(materials) {
		
	}
}