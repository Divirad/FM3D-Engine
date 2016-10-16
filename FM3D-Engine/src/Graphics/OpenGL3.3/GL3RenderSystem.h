#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

#ifdef _DEBUG
#define _GLErrorCheck(x) {\
				     GLenum GLCall_error = glGetError();\
				     if (GLCall_error != GL_NO_ERROR) {\
						std::cout << "[OpenGL Error] (" << GLCall_error << ": " << gluErrorString(GLCall_error) << "): " << #x << " " << __FILE__ << ":" << __LINE__ << std::endl;\
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
		void BeginRendering(float color[4]) override;
		void EndRendering() override;
		void Shutdown() override;

		Mesh* CreateMesh(const Skeleton* skeleton, bool supportsInstancing, const ArrayBase<Mesh::Part>& parts) const override { return new GL3Mesh(skeleton, supportsInstancing, parts); }
		Texture* CreateTexture(const char* filename) override { return new GL3Texture(); }
		Renderer2D* CreateRenderer2D() override { return new GL3Renderer2D(); }
		Renderer3D* CreateRenderer3D(Matrix4f& projectionMatrix, uint width, uint height) override { return new GL3Renderer3D(projectionMatrix, width, height, this); }
	};
}