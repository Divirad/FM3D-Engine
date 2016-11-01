#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL GL4RenderSystem : public GL3RenderSystem {
	protected:
		friend class RenderSystem;

		HDC m_hDevContext;
		HGLRC m_hGLRenderContext;

		GL4RenderSystem() {};
	public:
		Renderer2D* CreateRenderer2D(const RenderTarget2D* renderTarget) override { return new GL4Renderer2D(renderTarget); }
	};
}