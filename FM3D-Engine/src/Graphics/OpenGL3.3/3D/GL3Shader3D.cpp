#include <Engine.h>

namespace FM3D {

	using namespace std;

#define PATH "src/Graphics/OpenGL3.3/3D/Shader/"
#define MAX_BONES 128

	GL3Shader3D::GL3Shader3D()
		: GL3Shader(StringUtilities::StringWithDefines(FileManager::ReadShaderFile(PATH + string("Geometry.vert")),
		{ StringUtilities::Define {"MAX_BONES", std::to_string(MAX_BONES) } }).c_str(),
		FileManager::ReadShaderFile(PATH + string("Geometry.frag")).c_str()),
		m_boneBegin(0u), m_boneEnd(MAX_BONES-1) {
		
		m_WVPLocation = GetUniformLocation("gWVP");
		m_WorldMatrixLocation = GetUniformLocation("gWorld");
		m_colorTextureUnitLocation = GetUniformLocation("gColorMap");
		m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");
		m_bonesLocation = GetUniformLocation("gBones");


		GLCall(glVertexAttrib4f(GL3MESH_ATTRIBUTE_COLOR, 1.0f, 1.0f, 1.0f, 1.0f));
		GLCall(glVertexAttribI4i(GL3MESH_ATTRIBUTE_BONE_INDICES, 0, 0, 0, 0));
		GLCall(glVertexAttrib4f(GL3MESH_ATTRIBUTE_BONE_WEIGHTS, 0.0f, 0.0f, 0.0f, 0.0f));

		Bind();
		for (uint i = 0; i < MAX_BONES; i++) {
			SetUniformMat4(m_bonesLocation + i, Matrix4f::Transpose(Matrix4f::Identity()));
		}
		Unbind();
	}

	void GL3Shader3D::SetWVP(const Matrix4f& WVP) {
		SetUniformMat4(m_WVPLocation, WVP);
	}

	void GL3Shader3D::SetWorldMatrix(const Matrix4f& WVP) {
		SetUniformMat4(m_WorldMatrixLocation, WVP);
	}

	void GL3Shader3D::SetColorTextureUnit(unsigned int TextureUnit) {
		SetUniform1i(m_colorTextureUnitLocation, TextureUnit);
	}

	void GL3Shader3D::SetNormalTextureUnit(unsigned int TextureUnit) {
		SetUniform1i(m_normalTextureUnitLocation, TextureUnit);
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
}