#include "InternMesh.h"

using namespace FM3D;

namespace DesignerLib {

	InternMeshPart::InternMeshPart(FM3D_MeshPart * part) {
	}

	std::vector<InternVertex>* InternMeshPart::GetVertices() {
		auto result = new std::vector<InternVertex>(m_part->vertices.GetVertexCount());
		for (uint i = 0, c = m_part->vertices.GetVertexCount(); i < c; i++) {
			(*result)[i] = InternVertex {
				m_part->vertices.GetPosition(i).ToString(),
				m_part->vertices.GetTexCoord(i).ToString(),
				m_part->vertices.GetNormal(i).ToString(),
				m_part->vertices.GetColor(i).ToString(),
				m_part->vertices.GetBoneIndex(i).ToString(),
				m_part->vertices.GetBoneWeight(i).ToString(),
				m_part->vertices.GetTangent(i).ToString()
			};
		}
		return result;
	}
}