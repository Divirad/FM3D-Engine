#pragma once
#include <Engine.h>

#define GL3MESH_ATTRIBUTE_POSITION 0
#define GL3MESH_ATTRIBUTE_TEXCOORD 1
#define GL3MESH_ATTRIBUTE_NORMAL 2
#define GL3MESH_ATTRIBUTE_COLOR 3
#define GL3MESH_ATTRIBUTE_BONE_INDICES 4
#define GL3MESH_ATTRIBUTE_BONE_WEIGHTS 5

namespace FM3D {

	class GL3Mesh : public Mesh {
	private:
		struct Buffer {
			GLuint vao;
			GLuint vbo;
			GLuint ibo;
			GLuint ivbo;

			uint indicesCount;
			uint indexSize;
		};
		std::vector<Buffer> m_glBuffers;
	public:
		GL3Mesh(const Skeleton* skeleton, bool supportsInstancing, const ArrayBase<MeshPart>& parts);
		~GL3Mesh();

		void Bind(uint index) const;
		void Render(uint index, uint instanceCount = 0) const;
		static void Unbind();
	};
}