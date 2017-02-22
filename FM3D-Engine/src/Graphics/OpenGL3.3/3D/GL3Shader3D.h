#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3Shader3D : public GL3Shader {
	private:
		GLuint m_WVPLocation;
		GLuint m_WorldMatrixLocation;
		GLuint m_colorTextureUnitLocation;
		GLuint m_normalTextureUnitLocation;
		GLuint m_bonesLocation;
		uint m_boneBegin;
		uint m_boneEnd;
	public:
		GL3Shader3D();

		void SetWVP(const Matrix4f& WVP);
		void SetWorldMatrix(const Matrix4f& WVP);
		void SetColorTextureUnit(unsigned int TextureUnit);
		void SetNormalTextureUnit(unsigned int TextureUnit);
		void SetBones(const std::vector<Matrix4f>& bones);
		void ReSetBones(uint i);
	};
}