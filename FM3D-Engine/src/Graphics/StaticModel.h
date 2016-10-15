#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL StaticModel : public Model {
	public:
		struct VertexData {
			Vector3f position;
			Vector2f uv;
			Vector3f normal;
		};
		struct InstanceData {
			Matrix4f modelMatrix;
			uint color;
		};
		typedef unsigned int Index;
	protected:
		int m_vertexCount, m_indicesCount;
		StaticModel() : Model(0), m_vertexCount(0), m_indicesCount(0) {};
	public:
		virtual bool Initialize(int vertexCount, int indexCount, Index* indices, VertexData* vertices) = 0;
		virtual void Shutdown() = 0;

		inline int GetIndexCount() { return m_indicesCount; }
	};
}