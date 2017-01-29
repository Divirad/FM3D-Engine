#include <Engine.h>

namespace FM3D {

	Mesh::Mesh(const Skeleton* skeleton, bool supportsInstancing, int partsCount): m_skeleton(skeleton), m_supportsInstancing(supportsInstancing), m_partsCount(partsCount) {

	}

	MeshPart::MeshPart(uint p_indicesCount, void* p_indices, Vertices p_vertices, uint p_indexSize, bool p_supportsInstancing):
	indicesCount(p_indicesCount), indices(p_indices), vertices(p_vertices), indexSize(p_indexSize), supportsInstancing(p_supportsInstancing) {

	}
}