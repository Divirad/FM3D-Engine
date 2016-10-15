#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class GL3Shader3D : public GL3Shader {
	private:
		GLuint m_WVPLocation;
		GLuint m_WorldMatrixLocation;
		GLuint m_colorTextureUnitLocation;
		GLuint m_bonesLocation;
	public:
		GL3Shader3D();

		void SetWVP(const Matrix4f& WVP);
		void SetWorldMatrix(const Matrix4f& WVP);
		void SetColorTextureUnit(unsigned int TextureUnit);
		void SetBones(const Array<Matrix4f>& bones);
	};
}