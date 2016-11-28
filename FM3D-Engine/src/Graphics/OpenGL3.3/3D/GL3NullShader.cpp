#include <Engine.h>

namespace FM3D {
	using namespace std;
#define PATH "src/Graphics/OpenGL3.3/3D/Shader/"

	GL3NullShader::GL3NullShader() : GL3Shader(FileManager::ReadShaderFile(PATH + string("Null.vert")).c_str(), FileManager::ReadShaderFile(PATH + string("Null.frag")).c_str()) {
		m_WVPLocation = GetUniformLocation("gWVP");
	}

	void GL3NullShader::SetWVP(const Matrix4f& WVP) {
		SetUniformMat4(m_WVPLocation, WVP);
	}
}