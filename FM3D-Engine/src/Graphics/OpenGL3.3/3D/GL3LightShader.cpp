#include <Engine.h>

namespace ENGINE_NAME {
	using namespace std;
#define PATH "src/Graphics/OpenGL3.3/3D/Shader/"

	GL3LightShader::GL3LightShader(const char * vertSrc, const char * fragSrc) : GL3Shader(vertSrc, fragSrc) {
		m_WVPLocation = GetUniformLocation("gWVP");
		m_posTextureUnitLocation = GetUniformLocation("gPositionMap");
		m_colorTextureUnitLocation = GetUniformLocation("gColorMap");
		m_normalTextureUnitLocation = GetUniformLocation("gNormalMap");
		m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
		m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
		m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
		m_screenSizeLocation = GetUniformLocation("gScreenSize");
	}

	void GL3LightShader::SetEyeWorldPos(const Vector3f & EyeWorldPos) {
		SetUniform3f(m_eyeWorldPosLocation, EyeWorldPos);
	}

	void GL3LightShader::SetWVP(const Matrix4f & WVP) {
		SetUniformMat4(m_WVPLocation, WVP);
	}

	void GL3LightShader::Initialize(uint width, uint height) {
		SetUniform2f(m_screenSizeLocation, Vector2f(width, height));
		SetUniform1i(m_posTextureUnitLocation, 0);
		SetUniform1i(m_colorTextureUnitLocation, 1);
		SetUniform1i(m_normalTextureUnitLocation, 2);
	}

	GL3PointLightShader::GL3PointLightShader() : GL3LightShader(FileManager::ReadShaderFile(PATH + string("Light.vert")).c_str(), FileManager::ReadShaderFile(PATH + string("PointLight.frag")).c_str()) {
		m_pointLightLocation.Color = GetUniformLocation("gPointLight.Base.Color");
		m_pointLightLocation.AmbientIntensity = GetUniformLocation("gPointLight.Base.AmbientIntensity");
		m_pointLightLocation.Position = GetUniformLocation("gPointLight.Position");
		m_pointLightLocation.DiffuseIntensity = GetUniformLocation("gPointLight.Base.DiffuseIntensity");
		m_pointLightLocation.Atten.Constant = GetUniformLocation("gPointLight.Atten.Constant");
		m_pointLightLocation.Atten.Linear = GetUniformLocation("gPointLight.Atten.Linear");
		m_pointLightLocation.Atten.Exp = GetUniformLocation("gPointLight.Atten.Exp");
	}

	void GL3PointLightShader::SetPointLight(const PointLight& light) {
		SetUniform3f(m_pointLightLocation.Color, light.color);
		SetUniform1f(m_pointLightLocation.AmbientIntensity, light.ambientIntensity);
		SetUniform1f(m_pointLightLocation.DiffuseIntensity, light.diffuseIntensity);
		SetUniform3f(m_pointLightLocation.Position, light.position);
		SetUniform1f(m_pointLightLocation.Atten.Constant, light.attenuation.constant);
		SetUniform1f(m_pointLightLocation.Atten.Linear, light.attenuation.linear);
		SetUniform1f(m_pointLightLocation.Atten.Exp, light.attenuation.exp);
	}

	GL3DirectionalLightShader::GL3DirectionalLightShader() : GL3LightShader(FileManager::ReadShaderFile(PATH + string("Light.vert")).c_str(), FileManager::ReadShaderFile(PATH + string("DirectionalLight.frag")).c_str()) {
		m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
		m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
		m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
		m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	}

	void GL3DirectionalLightShader::SetDirectionalLight(const DirectionalLight & Light) {
		SetUniform3f(m_dirLightLocation.Color, Light.color);
		SetUniform1f(m_dirLightLocation.AmbientIntensity, Light.ambientIntensity);
		Vector3f direction = Light.direction;
		direction.Normalize();
		SetUniform3f(m_dirLightLocation.Direction, direction);
		SetUniform1f(m_dirLightLocation.DiffuseIntensity, Light.diffuseIntensity);
	}
}