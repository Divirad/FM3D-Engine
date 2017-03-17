#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Vertices {
	public:
		using Position = Vector3f;
		using TexCoord = Vector2f;
		using Normal = Vector3f;
		using Color = Vector4f;
		using BoneIndex = Vector4i;
		using BoneWeight = Vector4f;
		using Tangent = Vector3f;

		enum VertexData : byte {
			POSITION = 0x1,
			TEXCOORD = 0x2,
			NORMAL = 0x4,
			COLOR = 0x8,
			BONE_DATA = 0x10,
			TANGENT = 0x20,
		};
	private:
		uint m_vertexData;
		byte* m_data;
		uint m_vertexCount;

	public:
		Vertices(uint vertexCount, uint vertexData);
		Vertices(const Vertices&);
		Vertices(Vertices&&);
		~Vertices();
		Vertices& operator=(const Vertices& other);

		void SetPosition(const Position& value, uint index);
		void SetTexCoord(const TexCoord& value, uint index);
		void SetNormal(const Normal& value, uint index);
		void SetColor(const Color& value, uint index);
		void SetBoneIndex(const BoneIndex& value, uint index);
		void SetBoneWeight(const BoneWeight& value, uint index);
		void SetTangent(const Tangent& value, uint index);

		Position& GetPosition(uint index);
		TexCoord& GetTexCoord(uint index);
		Normal& GetNormal(uint index);
		Color& GetColor(uint index);
		BoneIndex& GetBoneIndex(uint index);
		BoneWeight& GetBoneWeight(uint index);
		Tangent& GetTangent(uint index);

		const Position& GetPosition(uint index) const;
		const TexCoord& GetTexCoord(uint index) const;
		const Normal& GetNormal(uint index) const;
		const Color& GetColor(uint index) const;
		const BoneIndex& GetBoneIndex(uint index) const;
		const BoneWeight& GetBoneWeight(uint index) const;
		const Tangent& GetTangent(uint index) const;

		uint OffsetOfPosition() const;
		uint OffsetOfTexCoord() const;
		uint OffsetOfNormal() const;
		uint OffsetOfColor() const;
		uint OffsetOfBoneIndex() const;
		uint OffsetOfBoneWeight() const;
		uint OffsetOfTangent() const;

		static uint SizeOfPosition();
		static uint SizeOfTexCoord();
		static uint SizeOfNormal();
		static uint SizeOfColor();
		static uint SizeOfBoneIndex();
		static uint SizeOfBoneWeight();
		static uint SizeOfTangent();

		static uint SizeOfBoneData();

		bool HasPositionData() const;
		bool HasTexCoordData() const;
		bool HasNormalData() const;
		bool HasColorData() const;
		bool HasBoneData() const;
		bool HasTangentData() const;

		uint GetVertexSize() const;
		uint GetVertexCount() const;
		uint GetVertexData() const;

		void SetData(const byte* data);
		byte* GetData();
		const byte* GetData() const;
	};
}