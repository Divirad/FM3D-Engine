#pragma once
#include <Engine.h>

namespace FM3D {

	class D3D11Shader : public Shader {
	private:
		struct MatrixBufferType {
			Matrix4f world;
			Matrix4f view;
			Matrix4f projection;
		};

		struct CameraBufferType {
			Vector3f cameraPosition;
			float padding;
		};

		struct LightBufferType {
			Vector4f ambientColor;
			Vector4f diffuseColor;
			Vector3f lightDirection;
			float specularPower;
			Vector4f specularColor;
		};

		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11InputLayout* m_layout;

		ID3D11SamplerState* m_sampleState;
		ID3D11Buffer* m_matrixBuffer;
		ID3D11Buffer* m_cameraBuffer;
		ID3D11Buffer* m_lightBuffer;

		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		const HWND m_hwnd;

		D3D11Shader(ID3D11Device* device, const HWND hwnd, ID3D11DeviceContext* context);
	public:

		bool Initialize(const char* vsFilename, const char* psFilename) override;
		void Shutdown() override;
		void Activate() override;
		bool SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix4f worldMatrix, Matrix4f viewMatrix,
			Matrix4f projectionMatrix, ID3D11ShaderResourceView* texture, Vector3f lightDirection,
			Vector4f ambientColor, Vector4f diffuseColor, Vector3f cameraPosition, Vector4f specularColor,
			float specularPower) override;
	private:
		void OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename);
		bool CreateBuffers();
		friend class D3D11RenderSystem;
	};
}