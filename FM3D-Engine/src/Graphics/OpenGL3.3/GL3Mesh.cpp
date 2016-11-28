#include <Engine.h>

namespace FM3D {

	GL3Mesh::GL3Mesh(const Skeleton* skeleton, bool supportsInstancing, const ArrayBase<Part>& parts): Mesh(skeleton, supportsInstancing, parts.Size()), m_glBuffers(parts.Size()) {
		bool isAnimated = skeleton != nullptr;

		for (uint p = 0; p < parts.Size(); p++) {
			const Part& part = parts[p];
			if (supportsInstancing && !part.supportsInstancing) throw new std::exception("Part of the mesh does not support instancing but whole mesh does");
			if (!isAnimated && part.vertices.HasBoneData()) throw std::exception("Part of the mesh is animated but the whole mesh is not");

			Buffer b;
			b.indicesCount = part.indicesCount;
			b.indexSize = part.indexSize;

			GLCall(glGenVertexArrays(1, &b.vao));

			GLCall(glGenBuffers(1, &b.vbo));
			uint s = part.vertices.GetVertexSize();
			GLCall(glBindVertexArray(b.vao));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, b.vbo));
			GLCall(glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(part.vertices.GetVertexCount() * part.vertices.GetVertexSize()), (const GLvoid*)part.vertices.GetData(), GL_STATIC_DRAW));

			//Enable Attributes
			GLCall(glEnableVertexAttribArray(GL3MESH_ATTRIBUTE_POSITION));
			GLCall(glEnableVertexAttribArray(GL3MESH_ATTRIBUTE_TEXCOORD));
			GLCall(glEnableVertexAttribArray(GL3MESH_ATTRIBUTE_NORMAL));
			if (part.vertices.HasColorData()) GLCall(glEnableVertexAttribArray(GL3MESH_ATTRIBUTE_COLOR));
			if (part.vertices.HasBoneData()) {
				GLCall(glEnableVertexAttribArray(GL3MESH_ATTRIBUTE_BONE_INDICES));
				GLCall(glEnableVertexAttribArray(GL3MESH_ATTRIBUTE_BONE_WEIGHTS));
			}
			
			//Set Attribute pointers
			GLCall(glVertexAttribPointer(GL3MESH_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, part.vertices.GetVertexSize(), (const GLvoid*)part.vertices.OffsetOfPosition()));
			GLCall(glVertexAttribPointer(GL3MESH_ATTRIBUTE_TEXCOORD, 2, GL_FLOAT, GL_FALSE, part.vertices.GetVertexSize(), (const GLvoid*)part.vertices.OffsetOfTexCoord()));
			GLCall(glVertexAttribPointer(GL3MESH_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, part.vertices.GetVertexSize(), (const GLvoid*)part.vertices.OffsetOfNormal()));
			if (part.vertices.HasColorData()) GLCall(glVertexAttribPointer(GL3MESH_ATTRIBUTE_COLOR, 4, GL_FLOAT, GL_FALSE, part.vertices.GetVertexSize(), (const GLvoid*)part.vertices.OffsetOfColor()));
			if (part.vertices.HasBoneData()) {
				GLCall(glVertexAttribIPointer(GL3MESH_ATTRIBUTE_BONE_INDICES, 4, GL_INT, part.vertices.GetVertexSize(), (const GLvoid*)part.vertices.OffsetOfBoneIndex()));
				GLCall(glVertexAttribPointer(GL3MESH_ATTRIBUTE_BONE_WEIGHTS, 4, GL_FLOAT, GL_FALSE, part.vertices.GetVertexSize(), (const GLvoid*)part.vertices.OffsetOfBoneWeight()));
			}

			//Instance Buffer
			if (part.supportsInstancing) {
				GLCall(glBindBuffer(GL_ARRAY_BUFFER, b.ibo));
				GLCall(glBufferData(GL_ARRAY_BUFFER, part.indicesCount * sizeof(InstanceData), 0, GL_DYNAMIC_DRAW));
				
				uint index = 3;
				if (part.vertices.HasColorData()) index += 1;
				if (part.vertices.HasBoneData()) index += 2;

				GLCall(glEnableVertexAttribArray(index));
				GLCall(glEnableVertexAttribArray(index + 1));
				GLCall(glEnableVertexAttribArray(index + 2));
				GLCall(glEnableVertexAttribArray(index + 3));
				GLCall(glEnableVertexAttribArray(index));

				GLCall(glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)0));
				GLCall(glVertexAttribPointer(index + 1, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)(sizeof(Vector4f))));
				GLCall(glVertexAttribPointer(index + 2, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)(2 * sizeof(Vector4f))));
				GLCall(glVertexAttribPointer(index + 3, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const GLvoid*)(3 * sizeof(Vector4f))));
				GLCall(glVertexAttribPointer(index, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(InstanceData), (const GLvoid*)(offsetof(InstanceData, color))));

				GLCall(glVertexAttribDivisor(index, 1));
				GLCall(glVertexAttribDivisor(index + 1, 1));
				GLCall(glVertexAttribDivisor(index + 2, 1));
				GLCall(glVertexAttribDivisor(index + 3, 1));
				GLCall(glVertexAttribDivisor(index + 4, 1));
			} else {
				b.ivbo = 0;
			}

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

			GLCall(glGenBuffers(1, &b.ibo));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.ibo));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, part.indicesCount * part.indexSize, part.indices, GL_STATIC_DRAW));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

			GLCall(glBindVertexArray(0));
			m_glBuffers[p] = b;
		}
	}
	
	GL3Mesh::~GL3Mesh() {
		for (Buffer& b : m_glBuffers) {
			GLCall(glDeleteBuffers(1, &b.ibo));
			if(b.ivbo != 0) GLCall(glDeleteBuffers(1, &b.ivbo));
			GLCall(glDeleteBuffers(1, &b.vbo));
			GLCall(glDeleteVertexArrays(1, &b.vao));
		}
	}

	void GL3Mesh::Bind(uint index) const {
		GLCall(glBindVertexArray(m_glBuffers[index].vao));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glBuffers[index].ibo));
	}

	void GL3Mesh::Unbind() {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		GLCall(glBindVertexArray(0));
	}

	static GLenum IndexSizeToGlEnum(uint indexSize) {
		switch (indexSize) {
		case 1:
			return GL_UNSIGNED_BYTE;
		case 2:
			return GL_UNSIGNED_SHORT;
		case 4:
			return GL_UNSIGNED_INT;
		default:
			throw std::exception();
		}
	}

	void GL3Mesh::Render(uint index, uint instanceCount) const {
		const Buffer& b = m_glBuffers[index];
		if (b.ivbo != 0) {
			GLCall(glDrawElementsInstanced(GL_TRIANGLES, b.indicesCount, IndexSizeToGlEnum(b.indexSize), NULL, instanceCount));
		} else {
			GLCall(glDrawElements(GL_TRIANGLES, b.indicesCount, IndexSizeToGlEnum(b.indexSize), NULL));
		}
	}
}