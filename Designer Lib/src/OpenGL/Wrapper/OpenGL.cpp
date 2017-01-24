#include "Opengl.h"
#define NO_FM3D
#include "../InternOpengl.h"
#include <cliext\vector>

using namespace  System::Windows::Media;
using namespace  System::Windows::Media::Imaging;

namespace DesignerLib {

	OpenGL::OpenGL() {
		m_gl = new InternOpenGL(static_cast<HINSTANCE>(System::Runtime::InteropServices::Marshal::GetHINSTANCE(OpenGL::GetType()->Module).ToPointer()));
	}

	OpenGL::~OpenGL() {
		delete m_gl;
	}

	void OpenGL::Initialize(double width, double height, Renderable^ r, DesignerLib::Camera^ cam) {
		m_gl->Initialize(width, height, cam->GetCamera(), Convert_From_Vec3(r->GetPosition()), Convert_From_Vec3(r->GetRotation()), Convert_From_Vec3(r->GetScale()), r->GetModel());
	}

	void OpenGL::ChangeSize(Size^ size) {
		m_gl->ChangeSize(size->Width, size->Height);
	}

	void OpenGL::Render(Image^ image) {
		auto bytes = m_gl->Render();
		cliext::vector<unsigned char> data(bytes.begin(), bytes.end());
		BitmapSource^ bitmapSource = BitmapSource::Create(m_gl->GetWidth(), m_gl->GetHeight(), 300, 300, PixelFormats::Bgra32, BitmapPalettes::Gray256, data.to_array(), m_gl->GetWidth() * 4);
	}

	void OpenGL::Update(Renderable^ renderable) {
		m_gl->Update(Convert_From_Vec3(renderable->GetPosition()), Convert_From_Vec3(renderable->GetRotation()), Convert_From_Vec3(renderable->GetScale()));
	}
}