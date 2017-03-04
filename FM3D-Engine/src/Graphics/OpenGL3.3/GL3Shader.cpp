#include <Engine.h>

namespace FM3D {

	GLuint GL3Shader::Initialize(const char* vertSrc, const char* fragSrc) {
		GLuint program = GLCall(glCreateProgram());
		GLuint vertex = GLCall(glCreateShader(GL_VERTEX_SHADER));
		GLuint fragment = GLCall(glCreateShader(GL_FRAGMENT_SHADER));

		GLCall(glShaderSource(vertex, 1, &vertSrc, NULL));
		GLCall(glCompileShader(vertex));

		GLint result;
		GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			GLCall(glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetShaderInfoLog(vertex, length, &length, &error[0]));
			std::cout << "Failed to compile vertex shader!" << std::endl;
			std::cout << &error[0] << std::endl;

			GLCall(glDeleteShader(vertex));
			return 0;
		}
		GLCall(glShaderSource(fragment, 1, &fragSrc, NULL));
		GLCall(glCompileShader(fragment));

		GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			GLCall(glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetShaderInfoLog(fragment, length, &length, &error[0]));
			std::cout << "Failed to compile fragment shader!" << std::endl;
			std::cout << &error[0] << std::endl;
			GLCall(glDeleteShader(fragment));
			return 0;
		}

		GLCall(glAttachShader(program, vertex));
		GLCall(glAttachShader(program, fragment));

		GLCall(glLinkProgram(program));

		GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetProgramInfoLog(program, length, &length, &error[0]));
			std::cout << "Failed to link shader program!" << std::endl;
			std::cout << &error[0] << std::endl;
			GLCall(glDeleteProgram(program));
			return 0;
		}

		GLCall(glValidateProgram(program));

		GLCall(glGetProgramiv(program, GL_VALIDATE_STATUS, &result));
		if (result == GL_FALSE) {
			GLint length;
			GLCall(glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length));
			std::vector<char> error(length);
			GLCall(glGetProgramInfoLog(program, length, &length, &error[0]));
			std::cout << "Failed to validate shader program!" << std::endl;
			std::cout << &error[0] << std::endl;
			GLCall(glDeleteProgram(program));
			return 0;
		}

		GLCall(glDeleteShader(vertex));
		GLCall(glDeleteShader(fragment));

		return program;
	}

	GL3Shader::GL3Shader(const char* vertPath, const char* fragPath) {
		m_ShaderID = Initialize(vertPath, fragPath);
	}

	GL3Shader::~GL3Shader() {
		GLCall(glDeleteProgram(m_ShaderID));
	}

	void GL3Shader::Bind() const {
		GLCall(glUseProgram(m_ShaderID));
	}

	void GL3Shader::Unbind() const {
		GLCall(glUseProgram(0));
	}

	GLint GL3Shader::GetUniformLocation(const GLchar* name) {
		GLint result = GLCall(glGetUniformLocation(m_ShaderID, name));
		if (result == -1)
			std::cout << "Could not find uniform " << name << " in shader!" << std::endl;

		return result;
	}

	void GL3Shader::SetUniform1f(GLint location, float value) {
		GLCall(glUniform1f(location, value));
	}

	void GL3Shader::SetUniform1fv(GLint location, float* value, int count) {
		GLCall(glUniform1fv(location, count, value));
	}

	void GL3Shader::SetUniform1i(GLint location, int value) {
		GLCall(glUniform1i(location, value));
	}

	void GL3Shader::SetUniform1iv(GLint location, int* value, int count) {
		GLCall(glUniform1iv(location, count, value));
	}

	void GL3Shader::SetUniform2f(GLint location, const Vector2f& vector) {
		GLCall(glUniform2f(location, vector.x, vector.y));
	}

	void GL3Shader::SetUniform3f(GLint location, const Vector3f& vector) {
		GLCall(glUniform3f(location, vector.x, vector.y, vector.z));
	}

	void GL3Shader::SetUniform4f(GLint location, const Vector4f& vector) {
		GLCall(glUniform4f(location, vector.x, vector.y, vector.z, vector.w));
	}

	void GL3Shader::SetUniformMat4(GLint location, const Matrix4f& matrix) {
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, matrix.elements));
	}

	void GL3Shader::BindAttribute(int attribute, const char* name) {

	}
}