#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class AnimatedModel : public Model {
	public:
		struct VertexData {
			Vector3f position;
			Vector2f uv;
			Vector3f normal;
			Vector4i boneIndex;
			Vector4f boneWeight;
		};
		typedef unsigned int Index;
	protected:
		int m_vertexCount, m_indicesCount;
		AnimatedModel() : Model(1), m_vertexCount(0), m_indicesCount(0) {};
	public:
		virtual bool Initialize(int vertexCount, int indexCount, Index* indices, VertexData* vertices) = 0;
		inline int GetIndexCount() { return m_indicesCount; }
	};
}