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

	Renderable^ OpenGL::Initialize(double width, double height, DesignerLib::Camera^ cam, Mesh^ mesh) {
		std::vector<FM3D::MeshPart*> parts;
		for each(auto p in mesh->Parts) {
			parts.push_back((p->GetIntern()->GetRaw()));
		}
		return gcnew Renderable(m_gl->Initialize(width, height, cam->GetCamera(), parts, mesh->Skelet != nullptr ? mesh->Skelet->GetIntern() : nullptr));
	}

	void OpenGL::ChangeSize(Size^ size) {
		m_gl->ChangeSize(size->Width, size->Height);
	}

	void OpenGL::Render(Image^ image) {
		auto bytes = m_gl->Render();
		std::reverse(bytes.begin(), bytes.end());
		cliext::vector<unsigned char> data(bytes.begin(), bytes.end());
		BitmapSource^ bitmapSource = BitmapSource::Create(m_gl->GetWidth(), m_gl->GetHeight(), 300, 300, PixelFormats::Rgb24, BitmapPalettes::Gray256, data.to_array(), m_gl->GetWidth() * 3);
		image->Source = bitmapSource;
	}

	void OpenGL::Update(Renderable^ renderable) {
		m_gl->Update(Convert_From_Vec3(renderable->GetPosition()), Convert_From_Vec3(renderable->GetRotation()), Convert_From_Vec3(renderable->GetScale()));
	}
}