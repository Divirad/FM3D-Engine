#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3NullShader : public GL3Shader {
	private:
		GLint m_WVPLocation;
	public:
		GL3NullShader();

		void SetWVP(const Matrix4f& WVP);
	};
}