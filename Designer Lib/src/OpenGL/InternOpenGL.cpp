#include "InternOpengl.h"
#include "../Global.h"

using namespace FM3D;
using namespace FM3D::EntitySystem;

namespace DesignerLib {

	InternOpenGL::InternOpenGL(HINSTANCE hInst) : m_hInst(hInst) {

	}

	InternOpenGL::~InternOpenGL() {
	}

	void InternOpenGL::Initialize(double width, double height, Camera* cam, float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz, const Model* model) {
		m_width = width;
		m_height = height;

		Global::Init();
		Window::StartConsole();

		m_renderSystem.reset(RenderSystem::Create(FM3D::Renderer::OpenGL3_3));
		auto ptr = Window::SetInstance(Window::Create(Platform::WINDOWS, m_hInst));
		m_window.reset(ptr);
		m_window->Start(2, 2, L"Backgound Window", false);


		if (!m_renderSystem->Initialize(m_width, m_height, false, static_cast<Win32Window*>(m_window.get())->GetHwnd(), false)) {
			MessageBoxA(NULL, "OpenGL Context failed to start!", "Error in DesignerLib", MB_OK);
			throw std::runtime_error("OpenGL Context failed to start!");
		}

		Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)m_width / (float)m_height, 0.1f, 10000.0f);
		m_renderTarget.reset(m_renderSystem->CreateRenderTarget2D(Vector2i(m_width, m_height), true));
		m_renderer.reset(m_renderSystem->CreateRenderer3D(projectionMatrix, m_width, m_height, m_renderTarget.get()));

		m_camera = cam;

		m_collection.reset(new EntityCollection());
		m_entity = m_collection->CreateEntity();
		m_entity->Add<PositionComponent>(Vector3f(x, y, z));
		m_entity->Add<RotationComponent>(Vector3f(rx, ry, rz));
		m_entity->Add<ScaleComponent>(Vector3f(sx, sy, sz));
		m_entity->Add<RenderableComponent>(model);
	}

	void InternOpenGL::ChangeSize(double width, double height) {
		m_width = static_cast<uint>(width);
		m_height = static_cast<uint>(height);

		throw std::runtime_error("Resizing is not implemented yet!");
	}

	std::vector<unsigned char> InternOpenGL::Render() {
		m_renderTarget->BindAsSource();

		std::vector<std::uint8_t> data(m_width * m_height * 4);
		return data;
	}

	void InternOpenGL::Update(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz) {
		m_entity->Get<PositionComponent>()->SetPosition(Vector3f(x, y, z));
		m_entity->Get<RotationComponent>()->SetRotation(Vector3f(rx, ry, rz));
		m_entity->Get<ScaleComponent>()->SetScale(Vector3f(sx, sy, sz));

		m_renderSystem->BeginRendering(FM3D::Color4f(0.0f, 0.0f, 0.0f, 1.0f));

		//m_renderer->Submit(m_entity.get());
		m_renderer->Flush(m_camera->GetViewMatrix(), m_camera->GetPosition());

		m_renderSystem->EndRendering();
	}
}