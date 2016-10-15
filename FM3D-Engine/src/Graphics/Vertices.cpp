#include <Engine.h>

namespace ENGINE_NAME {

	Vertices::Vertices(uint vertexCount, uint vertexData): m_vertexData(vertexData), m_data(new byte[GetVertexSize() * vertexCount]), m_vertexCount(vertexCount){

	}

	Vertices::Vertices(const Vertices& other): m_vertexData(other.m_vertexData), m_data(new byte[other.GetVertexSize() * other.m_vertexCount]), m_vertexCount(other.m_vertexCount) {
		memcpy(m_data, other.m_data, other.GetVertexSize() * other.m_vertexCount);
	}

	Vertices& Vertices::operator=(const Vertices& other) {
		m_vertexData = other.m_vertexData;
		m_data = new byte[other.GetVertexSize() * other.m_vertexCount];
		m_vertexCount = other.m_vertexCount;
		memcpy(m_data, other.m_data, other.GetVertexSize() * other.m_vertexCount);

		return *this;
	}

	Vertices::~Vertices() {
		delete[] m_data;
	}

	void Vertices::SetPosition(const Position& value, uint index) {
		Position* ptr = (Position*)(m_data + (GetVertexSize() * index) + OffsetOfPosition());
		*ptr = value;
	}

	void Vertices::SetTexCoord(const TexCoord& value, uint index) {
		TexCoord* ptr = (TexCoord*)(m_data + (GetVertexSize() * index) + OffsetOfTexCoord());
		*ptr = value;
	}

	void Vertices::SetNormal(const Normal& value, uint index) {
		Normal* ptr = (Normal*)(m_data + (GetVertexSize() * index) + OffsetOfNormal());
		*ptr = value;
	}

	void Vertices::SetColor(const Color& value, uint index) {
		Color* ptr = (Color*)(m_data + (GetVertexSize() * index) + OffsetOfColor());
		*ptr = value;
	}

	void Vertices::SetBoneIndex(const BoneIndex& value, uint index) {
		BoneIndex* ptr = (BoneIndex*)(m_data + (GetVertexSize() * index) + OffsetOfBoneIndex());
		*ptr = value;
	}

	void Vertices::SetBoneWeight(const BoneWeight& value, uint index) {
		BoneWeight* ptr = (BoneWeight*)(m_data + (GetVertexSize() * index) + OffsetOfBoneWeight());
		*ptr = value;
	}

	void Vertices::SetTangent(const Tangent& value, uint index) {
		Tangent* ptr = (Tangent*)(m_data + (GetVertexSize() * index) + OffsetOfTangent());
		*ptr = value;
	}

	Vertices::Position& Vertices::GetPosition(uint index) {
		return *((Position*)(m_data + (GetVertexSize() * index) + OffsetOfPosition()));
	}

	Vertices::TexCoord& Vertices::GetTexCoord(uint index) {
		return *((TexCoord*)(m_data + (GetVertexSize() * index) + OffsetOfTexCoord()));
	}

	Vertices::Normal& Vertices::GetNormal(uint index) {
		return *((Normal*)(m_data + (GetVertexSize() * index) + OffsetOfNormal()));
	}

	Vertices::Color& Vertices::GetColor(uint index) {
		return *((Color*)(m_data + (GetVertexSize() * index) + OffsetOfColor()));
	}
	
	Vertices::BoneIndex& Vertices::GetBoneIndex(uint index) {
		return *((BoneIndex*)(m_data + (GetVertexSize() * index) + OffsetOfBoneIndex()));
	}

	Vertices::BoneWeight& Vertices::GetBoneWeight(uint index) {
		return *((BoneWeight*)(m_data + (GetVertexSize() * index) + OffsetOfBoneWeight()));
	}

	Vertices::Tangent& Vertices::GetTangent(uint index) {
		return *((Tangent*)(m_data + (GetVertexSize() * index) + OffsetOfTangent()));
	}

	const Vertices::Position& Vertices::GetPosition(uint index) const {
		return *((Position*)(m_data + (GetVertexSize() * index) + OffsetOfPosition()));
	}

	const Vertices::TexCoord& Vertices::GetTexCoord(uint index) const {
		return *((TexCoord*)(m_data + (GetVertexSize() * index) + OffsetOfTexCoord()));
	}

	const Vertices::Normal& Vertices::GetNormal(uint index) const {
		return *((Normal*)(m_data + (GetVertexSize() * index) + OffsetOfNormal()));
	}

	const Vertices::Color& Vertices::GetColor(uint index) const {
		return *((Color*)(m_data + (GetVertexSize() * index) + OffsetOfColor()));
	}

	const Vertices::BoneIndex& Vertices::GetBoneIndex(uint index) const {
		return *((BoneIndex*)(m_data + (GetVertexSize() * index) + OffsetOfBoneIndex()));
	}

	const Vertices::BoneWeight& Vertices::GetBoneWeight(uint index) const {
		return *((BoneWeight*)(m_data + (GetVertexSize() * index) + OffsetOfBoneWeight()));
	}

	const Vertices::Tangent& Vertices::GetTangent(uint index) const {
		return *((Tangent*)(m_data + (GetVertexSize() * index) + OffsetOfTangent()));
	}

	uint Vertices::OffsetOfPosition() const {
		return 0u;
	}

	uint Vertices::OffsetOfTexCoord() const {
		return OffsetOfPosition() + HasPositionData() ? SizeOfPosition() : 0;
	}

	uint Vertices::OffsetOfNormal() const {
		return OffsetOfTexCoord() + (HasTexCoordData() ? SizeOfTexCoord() : 0);
	}

	uint Vertices::OffsetOfColor() const {
		return OffsetOfNormal() + (HasNormalData() ? SizeOfNormal() : 0);
	}

	uint Vertices::OffsetOfBoneIndex() const {
		return OffsetOfColor() + (HasColorData() ? SizeOfColor() : 0);
	}

	uint Vertices::OffsetOfBoneWeight() const {
		return OffsetOfBoneIndex() + (HasBoneData() ? SizeOfBoneIndex() : 0);
	}

	uint Vertices::OffsetOfTangent() const {
		return OffsetOfBoneWeight() + (HasBoneData() ? SizeOfBoneWeight() : 0);
	}

	uint Vertices::GetVertexSize() const {
		uint size = 0u;

		if (HasPositionData()) {
			size += SizeOfPosition();
		}
		if (HasTexCoordData()) {
			size += SizeOfTexCoord();
		}
		if (HasNormalData()) {
			size += SizeOfNormal();
		}
		if (HasColorData()) {
			size += SizeOfColor();
		}
		if (HasBoneData()) {
			size += SizeOfBoneData();
		}
		if (HasTangentData()) {
			size += SizeOfTangent();
		}

		return size;
	}

	bool Vertices::HasPositionData() const {
		return (m_vertexData & VertexData::POSITION) != 0;
	}

	bool Vertices::HasTexCoordData() const {
		return (m_vertexData & VertexData::TEXCOORD) != 0;
	}

	bool Vertices::HasNormalData() const {
		return (m_vertexData & VertexData::NORMAL) != 0;
	}

	bool Vertices::HasColorData() const {
		return (m_vertexData & VertexData::COLOR) != 0;
	}

	bool Vertices::HasBoneData() const {
		return (m_vertexData & VertexData::BONE_DATA) != 0;
	}

	bool Vertices::HasTangentData() const {
		return (m_vertexData & VertexData::TANGENT) != 0;
	}

	uint Vertices::GetVertexCount() const {
		return m_vertexCount;
	}

	uint Vertices::GetVertexData() const {
		return m_vertexData;
	}

	uint Vertices::SizeOfPosition() {
		return sizeof(Position);
	}

	uint Vertices::SizeOfTexCoord() {
		return sizeof(TexCoord);
	}

	uint Vertices::SizeOfNormal() {
		return sizeof(Normal);
	}

	uint Vertices::SizeOfColor() {
		return sizeof(Color);
	}

	uint Vertices::SizeOfBoneIndex() {
		return sizeof(BoneIndex);
	}

	uint Vertices::SizeOfBoneWeight() {
		return sizeof(BoneWeight);
	}

	uint Vertices::SizeOfTangent() {
		return sizeof(Tangent);
	}

	uint Vertices::SizeOfBoneData() {
		return SizeOfBoneIndex() + SizeOfBoneWeight();
	}

	byte* Vertices::GetData() {
		return m_data;
	}

	const byte* Vertices::GetData() const {
		return m_data;
	}
}