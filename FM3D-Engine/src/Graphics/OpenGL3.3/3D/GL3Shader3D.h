#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3Shader3D : public GL3Shader {
	public:
		enum ShaderConfig {
			STANDARD = 0x0,
			ANIMATED = 0x1,
			NORMALMAP = 0x2,
			SPECULARMAP = 0x4
		};
	private:
		GLuint m_WVPLocation;
		GLuint m_WorldMatrixLocation;
		GLuint m_colorTextureUnitLocation;
		GLuint m_normalTextureUnitLocation;
		GLuint m_bonesLocation;
		GLuint m_specularLocation;
		GLuint m_specularTextureUnitLocation;
		uint m_boneBegin;
		uint m_boneEnd;
	public:
		GL3Shader3D(int config);

		void SetWVP(const Matrix4f& WVP);
		void SetWorldMatrix(const Matrix4f& WVP);
		void SetColorTextureUnit(unsigned int textureUnit);
		void SetNormalTextureUnit(unsigned int textureUnit);
		void SetSpecularTextureUnit(unsigned int textureUnit);
		void SetBones(const std::vector<Matrix4f>& bones);
		void ReSetBones(uint i);
		void SetSpecular(float factor);
		std::vector<std::string> CreateDefines(int config);
	};
}