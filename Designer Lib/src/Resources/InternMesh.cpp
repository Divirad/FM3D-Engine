#include "InternMesh.h"
#include "../FileWriting.h"

using namespace FM3D;

namespace DesignerLib {

	InternMeshPart::InternMeshPart(FM3D::MeshPart* part): m_part(part) {
	}

	InternMeshPart::~InternMeshPart() {
		delete m_part;
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

	InternMeshPart* InternMeshPart::FromFile(std::ifstream& file) {
		uint indicesCount = ReadRawFromFile<uint>(file);
		uint indexSize = ReadRawFromFile<uint>(file);
		char* indices = new char[indicesCount * indexSize];
		file.read(indices, indicesCount * indexSize); //Indices
		uint vertexCount = ReadRawFromFile<uint>(file);
		uint vertexData = ReadRawFromFile<uint>(file);

		Vertices vertices(vertexCount, vertexData);
		char* verticesData = new char[vertexCount * vertices.GetVertexSize()];
		file.read(verticesData, vertexCount * vertices.GetVertexSize()); //Vertices
		vertices.SetData(reinterpret_cast<FM3D::byte*>(verticesData));

		bool supportsInstancing = ReadRawFromFile<bool>(file);

		return new InternMeshPart(new FM3D::MeshPart(indicesCount, static_cast<void*>(indices), std::move(vertices), indexSize, supportsInstancing));
	}
}