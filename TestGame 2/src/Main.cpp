#include <Engine.h>
#include <chrono>
#include <iomanip>

using ALL_FM3D_NAMESPACES;
using namespace FM3D::Math;

class TestPreset : public Preset {
private:
	IComponentArgs<PositionComponent>* m_pos;
public:
	TestPreset() {
		m_pos = new ComponentArgs<PositionComponent, Vector3f>(Vector3f(0.0f, 0.0f, 1.0f));
	}

	void SetComponents(EntityPtr e) override {
		m_pos->SetComponent(e);
	}
};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	Preset* p = new TestPreset();

	EntityCollection coll;

	auto e = coll.CreateEntity(p);

	std::cout << e->GetComponentsCount() << std::endl;

	 system("PAUSE");
}
