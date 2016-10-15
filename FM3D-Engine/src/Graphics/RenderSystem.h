#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class Model;
	class Texture;
	class Shader;

	class ENGINE_DLL RenderSystem {
	public:
		virtual bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen) = 0;
		virtual void BeginRendering(float color[4]) = 0;
		virtual void EndRendering() = 0;
		virtual void Shutdown() = 0;

		virtual Mesh* CreateMesh(const Skeleton* skeleton, bool supportsInstancing, SharedArray<Mesh::Part>& parts) const = 0;
		virtual Texture* CreateTexture(const char* filename) = 0;
		virtual Renderer2D* CreateRenderer2D() = 0;
		virtual Renderer3D* CreateRenderer3D(Matrix4f& projectionMatrix, uint width, uint height) = 0;

		static RenderSystem* Create(Renderer renderer);
	};
}