#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class D3D11Texture : Texture {
	private:
		struct TargaHeader {
			unsigned char data1[12];
			unsigned short width;
			unsigned short height;
			unsigned char bpp;
			unsigned char data2;
		};

		unsigned char* m_targaData;
		ID3D11Texture2D* m_texture;
		ID3D11ShaderResourceView* m_textureView;

		D3D11Texture(const char* filename, ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
			if (!Initialize(filename, device, deviceContext)) {
				std::cout << "ALAAAAAAAAAAARM Textur ist kaputt" << std::endl;
			}
		}
	public:
		inline ID3D11ShaderResourceView* GetTexture() { return m_textureView; }

		void Shutdown() override;
	private:
		bool Initialize(const char* filename, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
		bool LoadTarga(const char* filename, int& height, int& width);

		friend class D3D11RenderSystem;
	};
}