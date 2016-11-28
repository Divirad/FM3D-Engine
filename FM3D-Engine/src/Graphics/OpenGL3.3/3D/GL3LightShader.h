#pragma once
#include <Engine.h>

namespace FM3D {

	class GL3LightShader : public GL3Shader {
	private:
		GLint m_WVPLocation;
		GLint m_posTextureUnitLocation;
		GLint m_normalTextureUnitLocation;
		GLint m_colorTextureUnitLocation;
		GLint m_eyeWorldPosLocation;
		GLint m_matSpecularIntensityLocation;
		GLint m_matSpecularPowerLocation;
		GLint m_screenSizeLocation;
	protected:
		GL3LightShader(const char* vertSrc, const char* fragSrc);
	public:
		void SetEyeWorldPos(const Vector3f& EyeWorldPos);
		void SetWVP(const Matrix4f& WVP);
		void Initialize(uint width, uint height);
	};

	class GL3PointLightShader : public GL3LightShader {
	private:
		struct {
			GLint Color;
			GLint AmbientIntensity;
			GLint DiffuseIntensity;
			GLint Position;
			struct {
				GLint Constant;
				GLint Linear;
				GLint Exp;
			} Atten;
		} m_pointLightLocation;

	public:
		GL3PointLightShader();

		void SetPointLight(const PointLight& Lights);
	};

	class GL3DirectionalLightShader : public GL3LightShader {
	private:
		struct {
			GLint Color;
			GLint AmbientIntensity;
			GLint DiffuseIntensity;
			GLint Direction;
		} m_dirLightLocation;
	public:
		GL3DirectionalLightShader();

		void SetDirectionalLight(const DirectionalLight& Light);
	};
}