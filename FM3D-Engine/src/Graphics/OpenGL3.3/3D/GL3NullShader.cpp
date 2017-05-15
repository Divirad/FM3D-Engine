#include <Engine.h>

namespace FM3D {
	using namespace std;

	GL3NullShader::GL3NullShader() : GL3Shader(FileManager::ReadShaderFile("Null.vert", {}).c_str(), FileManager::ReadShaderFile("Null.frag", {}).c_str()) {
		m_WVPLocation = GetUniformLocation("gWVP");
	}

	void GL3NullShader::SetWVP(const Matrix4f& WVP) {
		SetUniformMat4(m_WVPLocation, WVP);
	}
}