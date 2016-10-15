#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class GL3NullShader : public GL3Shader {
	private:
		GLint m_WVPLocation;
	public:
		GL3NullShader();

		void SetWVP(const Matrix4f& WVP);
	};
}