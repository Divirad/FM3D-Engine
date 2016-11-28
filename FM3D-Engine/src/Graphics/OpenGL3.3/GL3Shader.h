#pragma once
#include <Engine.h>

namespace FM3D {

	class  ENGINE_DLL GL3Shader {
	private:
		GLuint m_ShaderID;
	public:
		GL3Shader(const char* vertSrc, const char* fragSource);
		~GL3Shader();

		void Bind() const;
		void Unbind() const;
	protected:
		void SetUniform1f(GLint location, float value);
		void SetUniform1fv(GLint location, float* value, int count);
		void SetUniform1i(GLint location, int value);
		void SetUniform1iv(GLint location, int* value, int count);
		void SetUniform2f(GLint location, const Vector2f& vector);
		void SetUniform3f(GLint location, const Vector3f& vector);
		void SetUniform4f(GLint location, const Vector4f& vector);
		void SetUniformMat4(GLint location, const Matrix4f& matrix);

		void BindAttribute(int attribute, const char* name);

		GLint GetUniformLocation(const GLchar* name);
	private:
		GLuint Initialize(const char* vertSrc, const char* fragSrc);
	};
}