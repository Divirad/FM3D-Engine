#include "Opengl.h"

namespace DesignerLib {

	OpenGL::OpenGL() {
		m_gl = new InternOpenGL(static_cast<HINSTANCE>(System::Runtime::InteropServices::Marshal::GetHINSTANCE(OpenGL::GetType()->Module).ToPointer()));
	}

	OpenGL::~OpenGL() {
		delete m_gl;
	}

	void OpenGL::Initialize(double width, double height) {
		m_gl->Initialize(width, height);
	}

	void OpenGL::ChangeSize(Size^ size) {
		m_gl->ChangeSize(size);
	}

	void OpenGL::Render(Image^ image) {
		m_gl->Render(image);
	}

	void OpenGL::Update() {
		m_gl->Update();
	}
}