#pragma once
#include "../pch.h"
#include "OpenGLContext.h"
#include "Wrapper\Renderable.h"
#include "Wrapper\Camera.h"

namespace DesignerLib {

	class InternOpenGL {
	private:
		HINSTANCE m_hInst;

		uint m_width;
		uint m_height;

		OpenGLContext m_context;

		std::unique_ptr<FM3D::RenderTarget2D> m_renderTarget;
		std::unique_ptr<FM3D::Renderer3D> m_renderer;
		std::unique_ptr<FM3D::RenderSystem> m_renderSystem;
		std::unique_ptr<FM3D::Window> m_window;
		std::unique_ptr<FM3D::EntityCollection> m_collection;
		FM3D::EntityPtr m_entity;
		FM3D::Camera* m_camera;
	public:
		InternOpenGL(HINSTANCE hInst);
		~InternOpenGL();

		void Initialize(double width, double height, Renderable^ r, DesignerLib::Camera^ cam);
		void ChangeSize(System::Windows::Size^ size);
		void Update();
		void Render(System::Windows::Controls::Image^ image);
	};
}