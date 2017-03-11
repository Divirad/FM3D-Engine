#include "InternMesh.h"
#include "../FileWriting.h"

using namespace FM3D;

namespace DesignerLib {

	InternMeshPart::InternMeshPart(FM3D::MeshPart* part): m_part(part) {
	}

	std::vector<InternVertex>* InternMeshPart::GetVertices() {
		auto result = new std::vector<InternVertex>(m_part->vertices.GetVertexCount());
		for (uint i = 0, c = m_part->vertices.GetVertexCount(); i < c; i++) {
			(*result)[i] = InternVertex {
				m_part->vertices.HasPositionData() ? m_part->vertices.GetPosition(i).ToString() : "",
				m_part->vertices.HasTexCoordData() ? m_part->vertices.GetTexCoord(i).ToString() : "",
				m_part->vertices.HasNormalData() ? m_part->vertices.GetNormal(i).ToString() : "",
				m_part->vertices.HasColorData() ? m_part->vertices.GetColor(i).ToString() : "",
				m_part->vertices.HasBoneData() ? m_part->vertices.GetBoneIndex(i).ToString() : "",
				m_part->vertices.HasBoneData() ? m_part->vertices.GetBoneWeight(i).ToString() : "",
				m_part->vertices.HasTangentData() ? m_part->vertices.GetTangent(i).ToString() : ""
			};
		}
		return result;
	}

	bool InternMeshPart::HasPositionData() { return m_part->vertices.HasPositionData(); }
	bool InternMeshPart::HasTexCoordData() { return m_part->vertices.HasTexCoordData(); }
	bool InternMeshPart::HasNormalData() { return m_part->vertices.HasNormalData(); }
	bool InternMeshPart::HasColorData() { return m_part->vertices.HasColorData(); }
	bool InternMeshPart::HasBoneData() { return m_part->vertices.HasBoneData(); }
	bool InternMeshPart::HasTangentData() { return m_part->vertices.HasTangentData(); }

	void InternMeshPart::WriteToFile(std::ofstream& file) {
		WriteRawToFile(file, m_part->indicesCount);
		WriteRawToFile(file, m_part->indexSize);
		file.write(reinterpret_cast<char*>(m_part->indices), m_part->indicesCount * m_part->indexSize); //Indices
		WriteRawToFile(file, m_part->vertices.GetVertexCount());
		WriteRawToFile(file, m_part->vertices.GetVertexData());
		file.write(reinterpret_cast<char*>(m_part->vertices.GetData()), m_part->vertices.GetVertexCount() * m_part->vertices.GetVertexSize()); //Vertices
		WriteRawToFile(file, m_part->supportsInstancing);
	}
}