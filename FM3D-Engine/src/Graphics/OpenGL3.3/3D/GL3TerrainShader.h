#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3TerrainShader : public GL3Shader {
	private:
		GLuint m_WVPLocation;
		GLuint m_WorldMatrixLocation;

		GLuint m_specularLocation0;
		GLuint m_colorTextureUnitLocation0;
		GLuint m_specularLocation1;
		GLuint m_colorTextureUnitLocation1;
		GLuint m_specularLocation2;
		GLuint m_colorTextureUnitLocation2;

		GLuint m_normalTextureUnitLocation;
		GLuint m_spatTextureUnitLocation;

		GLuint m_texCount;
	public:
		GL3TerrainShader();
		void SetWVP(const Matrix4f& WVP);
		void SetWorldMatrix(const Matrix4f& WVP);

		void SetColorTextureUnit0(unsigned int textureUnit);
		void SetColorTextureUnit1(unsigned int textureUnit);
		void SetColorTextureUnit2(unsigned int textureUnit);
		void SetSpecular0(float factor);
		void SetSpecular1(float factor);
		void SetSpecular2(float factor);

		void SetTexCount(float count);

		void SetNormalTextureUnit(unsigned int textureUnit);
		void SetSpatTextureUnit(unsigned int textureUnit);
	};
}