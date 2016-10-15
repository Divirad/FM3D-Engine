#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class D3D11Model;
	class D3D11Texture;
	class D3D11Shader;

	class ENGINE_DLL D3D11RenderSystem : public RenderSystem {
	private:
		bool m_vsync_enabled;
		int m_videoCardMemory;
		char m_videoCardDescription[128];
		IDXGISwapChain* m_swapChain;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11RasterizerState* m_rasterState;
		HWND m_hwnd;
	public:
		D3D11RenderSystem();
		bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen) override;
		void BeginRendering(float color[4]) override;
		void RenderModel(Model* model) override;
		void EndRendering() override;
		void Shutdown() override;

		Model* CreateModel();
		Texture* CreateTexture(const char* filename);

		inline ID3D11Device* GetDevice() { return m_device; }
		inline ID3D11DeviceContext* GetDeviceContext() { return m_deviceContext; }
	private:
		bool GetVideoCardInformation(int screenWidth, int screenHeight, unsigned int& numerator, unsigned int& denominator);
	};
}