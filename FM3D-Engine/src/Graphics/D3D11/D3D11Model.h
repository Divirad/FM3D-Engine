#pragma once
#include <Engine.h>

namespace FM3D {

	class D3D11Model : public Model {
	private:
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		D3D11Model(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	public:
		bool Initialize(int vertexCount, int indexCount, Index* indices, VertexData* vertices) override;
		void Shutdown() override;
		void Render() override;
	private:

		friend class D3D11RenderSystem;
	};
}