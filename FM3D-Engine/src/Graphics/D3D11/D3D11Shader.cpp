#include <Engine.h>

namespace FM3D {

	D3D11Shader::D3D11Shader(ID3D11Device* device, const HWND hwnd, ID3D11DeviceContext* context): m_vertexShader(0), m_pixelShader(0), m_layout(0), m_sampleState(0), m_device(device), m_hwnd(hwnd), m_deviceContext(context) {

	}

	bool D3D11Shader::SetShaderParameters(ID3D11DeviceContext* deviceContext, Matrix4f worldMatrix, Matrix4f viewMatrix,
		Matrix4f projectionMatrix, ID3D11ShaderResourceView* texture, Vector3f lightDirection,
		Vector4f ambientColor, Vector4f diffuseColor, Vector3f cameraPosition, Vector4f specularColor,
		float specularPower) {
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		unsigned int bufferNumber;
		MatrixBufferType* dataPtr;
		LightBufferType* dataPtr2;
		CameraBufferType* dataPtr3;

		// Lock the constant buffer so it can be written to.
		result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return false;
		}

		// Get a pointer to the data in the constant buffer.
		dataPtr = (MatrixBufferType*)mappedResource.pData;

		// Copy the matrices into the constant buffer.
		dataPtr->world = worldMatrix;
		dataPtr->view = viewMatrix;
		dataPtr->projection = projectionMatrix;

		// Unlock the constant buffer.
		deviceContext->Unmap(m_matrixBuffer, 0);

		// Set the position of the constant buffer in the vertex shader.
		bufferNumber = 0;

		// Now set the constant buffer in the vertex shader with the updated values.
		deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

		// Lock the camera constant buffer so it can be written to.
		result = deviceContext->Map(m_cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return false;
		}

		// Get a pointer to the data in the constant buffer.
		dataPtr3 = (CameraBufferType*)mappedResource.pData;

		// Copy the camera position into the constant buffer.
		dataPtr3->cameraPosition = cameraPosition;
		dataPtr3->padding = 0.0f;

		// Unlock the camera constant buffer.
		deviceContext->Unmap(m_cameraBuffer, 0);

		// Set the position of the camera constant buffer in the vertex shader.
		bufferNumber = 1;

		// Now set the camera constant buffer in the vertex shader with the updated values.
		deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_cameraBuffer);

		// Set shader texture resource in the pixel shader.
		deviceContext->PSSetShaderResources(0, 1, &texture);

		// Lock the light constant buffer so it can be written to.
		result = deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result)) {
			return false;
		}

		// Get a pointer to the data in the light constant buffer.
		dataPtr2 = (LightBufferType*)mappedResource.pData;

		// Copy the lighting variables into the light constant buffer.
		dataPtr2->ambientColor = ambientColor;
		dataPtr2->diffuseColor = diffuseColor;
		dataPtr2->lightDirection = lightDirection;
		dataPtr2->specularColor = specularColor;
		dataPtr2->specularPower = specularPower;

		// Unlock the light constant buffer.
		deviceContext->Unmap(m_lightBuffer, 0);

		// Set the position of the light constant buffer in the pixel shader.
		bufferNumber = 0;

		// Finally set the light constant buffer in the pixel shader with the updated values.
		deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

		return true;
	}

	bool D3D11Shader::CreateBuffers() {
		D3D11_SAMPLER_DESC samplerDesc;
		D3D11_BUFFER_DESC matrixBufferDesc;
		D3D11_BUFFER_DESC cameraBufferDesc;
		D3D11_BUFFER_DESC lightBufferDesc;

		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		// Create the texture sampler state.
		HRESULT result = m_device->CreateSamplerState(&samplerDesc, &m_sampleState);
		if (FAILED(result)) {
			return false;
		}

		// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
		matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
		matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		matrixBufferDesc.MiscFlags = 0;
		matrixBufferDesc.StructureByteStride = 0;

		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		result = m_device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
		if (FAILED(result)) {
			return false;
		}

		// Setup the description of the camera dynamic constant buffer that is in the vertex shader.
		cameraBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		cameraBufferDesc.ByteWidth = sizeof(CameraBufferType);
		cameraBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cameraBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cameraBufferDesc.MiscFlags = 0;
		cameraBufferDesc.StructureByteStride = 0;

		// Create the camera constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		result = m_device->CreateBuffer(&cameraBufferDesc, NULL, &m_cameraBuffer);
		if (FAILED(result)) {
			return false;
		}

		// Setup the description of the light dynamic constant buffer that is in the pixel shader.
		// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
		lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		lightBufferDesc.ByteWidth = sizeof(LightBufferType);
		lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		lightBufferDesc.MiscFlags = 0;
		lightBufferDesc.StructureByteStride = 0;

		// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
		result = m_device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
		if (FAILED(result)) {
			return false;
		}

		return true;
	}

	bool D3D11Shader::Initialize(const char* vsFilename, const char* psFilename) {
		HRESULT result;
		ID3D10Blob* errorMessage;
		ID3D10Blob* vertexShaderBuffer;
		ID3D10Blob* pixelShaderBuffer;

		errorMessage = 0;
		vertexShaderBuffer = 0;
		pixelShaderBuffer = 0;

		int vsFilenameLength = 0, psFilenameLength = 0;
		while (vsFilename[vsFilenameLength] != 0) vsFilenameLength++;
		while (psFilename[psFilenameLength] != 0) psFilenameLength++;
		WCHAR* vsFilenameWCHAR = new WCHAR[vsFilenameLength+1];
		WCHAR* psFilenameWCHAR = new WCHAR[psFilenameLength+1];

		MultiByteToWideChar(0, 0, vsFilename, vsFilenameLength+1, vsFilenameWCHAR, vsFilenameLength+1);
		MultiByteToWideChar(0, 0, psFilename, psFilenameLength+1, psFilenameWCHAR, psFilenameLength+1);

		//vsFilenameWCHAR = L"light.vs";
		//psFilenameWCHAR = L"light.ps";

		result = D3DCompileFromFile(vsFilenameWCHAR, NULL, NULL, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
		if (FAILED(result)) {
			if (errorMessage) {
				OutputShaderErrorMessage(errorMessage, vsFilenameWCHAR);
			}
			else {
				MessageBox(m_hwnd, vsFilenameWCHAR, L"Missing Shader File", MB_OK);
			}

			return false;
		}

		result = D3DCompileFromFile(psFilenameWCHAR, NULL, NULL, "LightPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);
		if (FAILED(result)) {
			if (errorMessage) {
				OutputShaderErrorMessage(errorMessage, psFilenameWCHAR);
			}
			else {
				MessageBox(m_hwnd, psFilenameWCHAR, L"Missing Shader File", MB_OK);
			}

			return false;
		}

		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
		if (FAILED(result)) {
			return false;
		}

		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
		if (FAILED(result)) {
			return false;
		}

		D3D11_INPUT_ELEMENT_DESC polygonLayout[3];

		polygonLayout[0].SemanticName = "POSITION";
		polygonLayout[0].SemanticIndex = 0;
		polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[0].InputSlot = 0;
		polygonLayout[0].AlignedByteOffset = 0;
		polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[0].InstanceDataStepRate = 0;

		polygonLayout[1].SemanticName = "TEXCOORD";
		polygonLayout[1].SemanticIndex = 0;
		polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
		polygonLayout[1].InputSlot = 0;
		polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[1].InstanceDataStepRate = 0;

		polygonLayout[2].SemanticName = "NORMAL";
		polygonLayout[2].SemanticIndex = 0;
		polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		polygonLayout[2].InputSlot = 0;
		polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		polygonLayout[2].InstanceDataStepRate = 0;

		unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

		// Create the vertex input layout.
		result = m_device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
			&m_layout);
		if (FAILED(result)) {
			return false;
		}

		// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
		vertexShaderBuffer->Release();
		vertexShaderBuffer = 0;

		pixelShaderBuffer->Release();
		pixelShaderBuffer = 0;

		return CreateBuffers();
	}

	void D3D11Shader::Shutdown() {
		if (m_lightBuffer) {
			m_lightBuffer->Release();
			m_lightBuffer = 0;
		}

		// Release the camera constant buffer.
		if (m_cameraBuffer) {
			m_cameraBuffer->Release();
			m_cameraBuffer = 0;
		}

		// Release the matrix constant buffer.
		if (m_matrixBuffer) {
			m_matrixBuffer->Release();
			m_matrixBuffer = 0;
		}

		// Release the sampler state.
		if (m_sampleState) {
			m_sampleState->Release();
			m_sampleState = 0;
		}

		// Release the layout.
		if (m_layout) {
			m_layout->Release();
			m_layout = 0;
		}

		// Release the pixel shader.
		if (m_pixelShader) {
			m_pixelShader->Release();
			m_pixelShader = 0;
		}

		// Release the vertex shader.
		if (m_vertexShader) {
			m_vertexShader->Release();
			m_vertexShader = 0;
		}
	}

	void D3D11Shader::Activate() {
		m_deviceContext->IASetInputLayout(m_layout);

		// Set the vertex and pixel shaders that will be used to render this triangle.
		m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
		m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);

		// Set the sampler state in the pixel shader.
		m_deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	}

	void D3D11Shader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, WCHAR* shaderFilename) {
		char* compileErrors;
		unsigned long bufferSize, i;
		std::ofstream fout;

		compileErrors = (char*)(errorMessage->GetBufferPointer());

		bufferSize = (unsigned long) errorMessage->GetBufferSize();

		fout.open("shader-error.txt");

		for (i = 0; i<bufferSize; i++) {
			fout << compileErrors[i];
		}

		fout.close();

		errorMessage->Release();
		errorMessage = 0;

		MessageBox(m_hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

		return;
	}
}