#include <Engine.h>
#include <chrono>
#include <iomanip>

using ALL_FM3D_NAMESPACES;
using namespace FM3D::Math;

class RotLogic : public EntityLogic {
	void Execute(EntityPtr entity) override {
		std::cout << entity->Get<PositionComponent>()->GetPosition().x << std::endl;
	}
public:
	RotLogic(EntityCollection& coll) : EntityLogic(coll.GetGroup(Matcher().AllOf({ RotationComponentId }))) {};
};

class ScaleLogic : public EntityLogic {
	void Execute(EntityPtr entity) override {
		std::cout << entity->Get<PositionComponent>()->GetPosition().x << std::endl;
	}
public:
	ScaleLogic(EntityCollection& coll) : EntityLogic(coll.GetGroup(Matcher().AllOf({ ScaleComponentId }))) {};
};

class ScaleRotLogic : public EntityLogic {
	void Execute(EntityPtr entity) override {
		std::cout << entity->Get<PositionComponent>()->GetPosition().x << std::endl;
	}
public:
	ScaleRotLogic(EntityCollection& coll) : EntityLogic(coll.GetGroup(Matcher().AllOf({ ScaleComponentId, RotationComponentId }))) {};
};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	EntityCollection coll;

	coll.CreateEntity()->Add<PositionComponent>(Vector3f(1.0f, 0.0f, 0.0f))->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(2.0f, 0.0f, 0.0f))->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(3.0f, 0.0f, 0.0f))->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(4.0f, 0.0f, 0.0f))->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(5.0f, 0.0f, 0.0f))->Add<ScaleComponent>(Vector3f(0.0f, 0.0f, 0.0f))->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(6.0f, 0.0f, 0.0f))->Add<ScaleComponent>(Vector3f(0.0f, 0.0f, 0.0f))->Add<RotationComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(7.0f, 0.0f, 0.0f))->Add<ScaleComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(8.0f, 0.0f, 0.0f))->Add<ScaleComponent>(Vector3f(0.0f, 0.0f, 0.0f));
	coll.CreateEntity()->Add<PositionComponent>(Vector3f(9.0f, 0.0f, 0.0f))->Add<ScaleComponent>(Vector3f(0.0f, 0.0f, 0.0f));

	EntityLogicCollection lcoll;
	EntityLogicPtr rotLogic(new RotLogic(coll));
	EntityLogicPtr scaleLogic(new ScaleLogic(coll));
	EntityLogicPtr scaleRotLogic(new ScaleRotLogic(coll));
	lcoll.Add(rotLogic);
	lcoll.Add(scaleLogic);

	 rotLogic->ExecuteForAll(); std::cout << std::endl;
	 scaleLogic->ExecuteForAll(); std::cout << std::endl;
	 scaleRotLogic->ExecuteForAll(); std::cout << std::endl;
	 lcoll.Execute(); std::cout << std::endl;

	 system("PAUSE");
}
