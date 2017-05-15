#include <Engine.h>

namespace FM3D {

	GL3TerrainShader::GL3TerrainShader() : GL3Shader(FileManager::ReadShaderFile("Terrain.vert", {}).c_str(), FileManager::ReadShaderFile("Terrain.frag", {}).c_str()) {
		m_WVPLocation = GetUniformLocation("gWVP");
		m_WorldMatrixLocation = GetUniformLocation("gWorld");
		m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");
		m_spatTextureUnitLocation = GetUniformLocation("gSpatMap");

		m_colorTextureUnitLocation0 = GetUniformLocation("gColorMap0");
		m_specularLocation0 = GetUniformLocation("gSpecularFactor0");
		m_colorTextureUnitLocation1 = GetUniformLocation("gColorMap1");
		m_specularLocation1 = GetUniformLocation("gSpecularFactor1");
		m_colorTextureUnitLocation2 = GetUniformLocation("gColorMap2");
		m_specularLocation2 = GetUniformLocation("gSpecularFactor2");
		m_texCount = GetUniformLocation("gtexCount");
	}

	void GL3TerrainShader::SetWVP(const Matrix4f& WVP) {
		SetUniformMat4(m_WVPLocation, WVP);
	}

	void GL3TerrainShader::SetWorldMatrix(const Matrix4f& WVP) {
		SetUniformMat4(m_WorldMatrixLocation, WVP);
	}

	void GL3TerrainShader::SetColorTextureUnit0(unsigned int textureUnit) {
		SetUniform1i(m_colorTextureUnitLocation0, textureUnit);
	}

	void GL3TerrainShader::SetSpecular0(float factor) {
		SetUniform1f(m_specularLocation0, factor);
	}

	void GL3TerrainShader::SetColorTextureUnit1(unsigned int textureUnit) {
		SetUniform1i(m_colorTextureUnitLocation1, textureUnit);
	}

	void GL3TerrainShader::SetSpecular1(float factor) {
		SetUniform1f(m_specularLocation1, factor);
	}

	void GL3TerrainShader::SetColorTextureUnit2(unsigned int textureUnit) {
		SetUniform1i(m_colorTextureUnitLocation2, textureUnit);
	}

	void GL3TerrainShader::SetSpecular2(float factor) {
		SetUniform1f(m_specularLocation2, factor);
	}

	void GL3TerrainShader::SetTexCount(float count) {
		SetUniform1f(m_texCount, count);
	}

	void GL3TerrainShader::SetNormalTextureUnit(unsigned int textureUnit) {
		SetUniform1i(m_normalTextureUnitLocation, textureUnit);
	}

	void GL3TerrainShader::SetSpatTextureUnit(unsigned int textureUnit) {
		SetUniform1i(m_spatTextureUnitLocation, textureUnit);
	}
}