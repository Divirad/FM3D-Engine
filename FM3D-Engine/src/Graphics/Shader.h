#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Shader {
	public:
		virtual bool Initialize(const char* vsFilename, const char* psFilename) = 0;
		virtual void Shutdown() = 0;
		virtual void Activate() = 0;
		virtual bool SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix4f worldMatrix, Matrix4f viewMatrix,
			Matrix4f projectionMatrix, ID3D11ShaderResourceView* texture, Vector3f lightDirection,
			Vector4f ambientColor, Vector4f diffuseColor, Vector3f cameraPosition, Vector4f specularColor,
			float specularPower) = 0;
	};
}