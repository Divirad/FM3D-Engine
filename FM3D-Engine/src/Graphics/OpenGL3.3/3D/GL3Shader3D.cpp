#include <Engine.h>

namespace FM3D {

	using namespace std;

#define MAX_BONES 128

	GL3Shader3D::GL3Shader3D(int config)
		: GL3Shader(StringUtilities::StringWithDefines(FileManager::ReadShaderFile("Geometry.vert", CreateDefines(config)),
		{ StringUtilities::Define{ "MAX_BONES", std::to_string(MAX_BONES) } }).c_str(),
			FileManager::ReadShaderFile("Geometry.frag", CreateDefines(config)).c_str()),
		m_boneBegin(0u), m_boneEnd(MAX_BONES-1) {
		
		m_WVPLocation = GetUniformLocation("gWVP");
		m_WorldMatrixLocation = GetUniformLocation("gWorld");
		m_colorTextureUnitLocation = GetUniformLocation("gColorMap");
		m_normalTextureUnitLocation = config & NORMALMAP ? GetUniformLocation("gNormalMap") : -1;
		m_specularTextureUnitLocation = config & SPECULARMAP ? GetUniformLocation("gSpecularMap") : -1;
		m_specularLocation = GetUniformLocation("gSpecularFactor");
		m_bonesLocation = config & ANIMATED ? GetUniformLocation("gBones") : -1;


		GLCall(glVertexAttrib4f(GL3MESH_ATTRIBUTE_COLOR, 1.0f, 1.0f, 1.0f, 1.0f));
		GLCall(glVertexAttribI4i(GL3MESH_ATTRIBUTE_BONE_INDICES, 0, 0, 0, 0));
		GLCall(glVertexAttrib4f(GL3MESH_ATTRIBUTE_BONE_WEIGHTS, 0.0f, 0.0f, 0.0f, 0.0f));
		GLCall(glVertexAttrib3f(GL3MESH_ATTRIBUTE_TANGENT, 0.0f, 0.0f, 0.0f));

		if (config & ANIMATED) {
			Bind();
			for (uint i = 0; i < MAX_BONES; i++) {
				SetUniformMat4(m_bonesLocation + i, Matrix4f::Transpose(Matrix4f::Identity()));
			}
			Unbind();
		}
	}

	void GL3Shader3D::SetWVP(const Matrix4f& WVP) {
		SetUniformMat4(m_WVPLocation, WVP);
	}

	void GL3Shader3D::SetWorldMatrix(const Matrix4f& WVP) {
		SetUniformMat4(m_WorldMatrixLocation, WVP);
	}

	void GL3Shader3D::SetColorTextureUnit(unsigned int textureUnit) {
		SetUniform1i(m_colorTextureUnitLocation, textureUnit);
	}

	void GL3Shader3D::SetNormalTextureUnit(unsigned int textureUnit) {
		SetUniform1i(m_normalTextureUnitLocation, textureUnit);
	}

	void GL3Shader3D::SetSpecularTextureUnit(unsigned int textureUnit) {
		SetUniform1i(m_specularTextureUnitLocation, textureUnit);
	}

	void GL3Shader3D::SetBones(const std::vector<Matrix4f>& bones) {
		for (uint i = 0; i < bones.size(); i ++) {
			SetUniformMat4(m_bonesLocation + i, Matrix4f::Transpose(bones[i]));
		}
		if (bones.size() > m_boneEnd) m_boneEnd = bones.size();
		m_boneBegin = 0;
	}

	void GL3Shader3D::ReSetBones(uint i) {
		for (uint b = m_boneBegin; b < m_boneEnd && b < i; b++) {
			SetUniformMat4(m_bonesLocation + b, Matrix4f::Transpose(Matrix4f::Identity()));
		}
	}

	void GL3Shader3D::SetSpecular(float factor) {
		SetUniform1f(m_specularLocation, factor);
	}

	std::vector<string> GL3Shader3D::CreateDefines(int config) {
		std::vector<std::string> defines;
		if (config & ANIMATED) defines.push_back("Animated");
		if (config & NORMALMAP) defines.push_back("Normalmap");
		if (config & SPECULARMAP) defines.push_back("Specularmap");
		return defines;
	}
}