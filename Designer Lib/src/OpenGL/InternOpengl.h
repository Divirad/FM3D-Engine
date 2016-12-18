#pragma once
#include "../pch.h"
#include "OpenGLContext.h"
#include "IRenderable.h"

namespace DesignerLib {

	class InternOpenGL {
	private:
		GLuint m_fbo;
		GLuint m_renderBuffer;

		uint m_width;
		uint m_height;

		OpenGLContext m_context;
	public:
		InternOpenGL(HINSTANCE hInst);
		~InternOpenGL();

		void Initialize(double width, double height);
		void ChangeSize(System::Windows::Size^ size);
		void Update(IRenderable^ r);
		void Render(System::Windows::Controls::Image^ image);
	};
}