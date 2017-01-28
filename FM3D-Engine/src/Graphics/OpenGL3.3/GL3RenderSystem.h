#pragma once
#include <Engine.h>

namespace FM3D {

#ifdef _DEBUG
#define _GLErrorCheck(x) {\
				     GLenum GLCall_error = glGetError();\
				     if (GLCall_error != GL_NO_ERROR) {\
						std::stringstream errorStream;\
						errorStream << GLCall_error << ": " << gluErrorString(GLCall_error) << ": " << #x;\
						std::string errorStr = errorStream.str();\
						OUTPUT_ERROR(1, "OpenGL Error", errorStr); \
						__debugbreak();\
				     }\
					 }
#endif

#ifdef _DEBUG
#define GLCall(x) x;\
				  _GLErrorCheck(x);
#define GLErrorCheck() _GLErrorCheck(0)
#else
#define GLCall(x) x;
#define GLErrorCheck()
#endif

	class ENGINE_DLL GL3RenderSystem : public RenderSystem {
	protected:
		friend class RenderSystem;

		HDC m_hDevContext;
		HGLRC m_hGLRenderContext;

		GL3RenderSystem() {};
	public:
		bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen) override;
		void BeginRendering(const Color4f& color) override;
		void EndRendering() override;
		void Shutdown() override;

		Mesh* CreateMesh(const Skeleton* skeleton, bool supportsInstancing, const ArrayBase<MeshPart>& parts) const override { return new GL3Mesh(skeleton, supportsInstancing, parts); }
		Texture* CreateTexture() override { return new GL3Texture(); }
		Renderer2D* CreateRenderer2D(const RenderTarget2D* renderTarget) override { return new GL3Renderer2D(renderTarget); }
		Renderer3D* CreateRenderer3D(Matrix4f& projectionMatrix, uint width, uint height, RenderTarget2D* target) override { return new GL3Renderer3D(projectionMatrix, width, height, this, target); }
		RenderTarget2D* CreateRenderTarget2D(const Vector2i& size, bool useDepth) override { return new GL3RenderTarget2D(size, useDepth); }
	};
}