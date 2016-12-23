#include "InternOpengl.h"
#include "../pch.h"
#include <cliext/vector>  

using namespace System::Windows::Media;
using namespace System::Windows::Media::Imaging;

using namespace FM3D;

namespace DesignerLib {

	InternOpenGL::InternOpenGL(HINSTANCE hInst) : m_hInst(hInst), m_context(hInst) {

	}

	InternOpenGL::~InternOpenGL() {
	}

	void InternOpenGL::Initialize(double width, double height, Renderable^ r, DesignerLib::Camera^ cam) {
		m_width = width;
		m_height = height;

		if (!m_context.Initialize()) {
			MessageBoxA(NULL, "OpenGL Context failed to start!", "Error in DesignerLib", MB_OK);
			throw std::runtime_error("OpenGL Context failed to start!");
		}

		Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)m_width / (float)m_height, 0.1f, 10000.0f);

		m_renderSystem.reset(RenderSystem::Create(OpenGL3_3));
		m_window.reset(Window::Create(Platform::WINDOWS, m_hInst));
		m_window->Start(1, 1, L"Background Window", false);
		if (!m_renderSystem->Initialize(m_width, m_window->GetHeight(), true, ((Win32Window*)m_window.get())->GetHwnd(), false)) {
			MessageBoxA(NULL, "Rendersystem Initializing failed!", "Error in DesignerLib", MB_OK);
			throw std::runtime_error("Rendersystem Initializing failed!");
		}
		m_renderTarget.reset(m_renderSystem->CreateRenderTarget2D(Vector2i(m_width, m_height), true));
		m_renderer.reset(m_renderSystem->CreateRenderer3D(projectionMatrix, m_width, m_height, m_renderTarget.get()));

		m_collection.reset(new EntityCollection());
		m_entity = m_collection->CreateEntity();
		m_entity->Add<PositionComponent>(Vector3f(0.0f, 0.0f, 0.0f));
		m_entity->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
		m_entity->Add<ScaleComponent>(Vector3f(1.0f, 1.0f, 1.0f));
		Model* model = NULL;
		m_entity->Add<RenderableComponent>(model);

		r->SetEntity(m_entity.get());
	}

	void InternOpenGL::ChangeSize(System::Windows::Size^ size) {
		m_width = static_cast<uint>(size->Width);
		m_height = static_cast<uint>(size->Height);

		throw std::runtime_error("Resizing is not implemented yet!");
	}

	void InternOpenGL::Render(System::Windows::Controls::Image^ image) {
		m_renderTarget->BindAsSource();

		std::vector<std::uint8_t> data(m_width * m_height * 4);
		GLCall(glReadBuffer(GL_COLOR_ATTACHMENT0));
		GLCall(glReadPixels(0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE, &data[0]));

		cliext::vector<std::uint8_t> d(data.begin(), data.end());

		BitmapSource^ bitmapSource = BitmapSource::Create(m_width, m_height, 300, 300, PixelFormats::Bgra32, BitmapPalettes::Gray256, d.to_array(), m_width * 4);

		GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
	}

	void InternOpenGL::Update() {
		m_renderSystem->BeginRendering(FM3D::Color4f(0.0f, 0.0f, 0.0f, 1.0f));

		m_renderer->Submit(m_entity.get());
		m_renderer->Flush(m_camera->GetViewMatrix(), m_camera->GetPosition());

		m_renderSystem->EndRendering();
	}
}