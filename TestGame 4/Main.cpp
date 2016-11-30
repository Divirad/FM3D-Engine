#include <Engine.h>

using namespace FM3D;
using namespace std;

void PrintData(EntityCollection& c);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	EntityCollection coll;
	{
		PrintData(coll);
		EntityPtr e = coll.CreateEntity();
		EntityPtr e2 = coll.CreateEntity()->Add<PositionComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		coll.CreateEntity()->Add<PositionComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		coll.CreateEntity()->Add<ScaleComponent>(Vector3f(0.0f, 5.0f, 2.0f))->Add<PositionComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		coll.CreateEntity()->Add<PositionComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		coll.CreateEntity()->Add<RotationComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		coll.CreateEntity()->Add<PositionComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		e->Add<PositionComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		e->Add<RotationComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		e->Add<ScaleComponent>(Vector3f(0.0f, 5.0f, 2.0f));

		auto group = coll.GetGroup(Matcher().AllOf(ComponentIdList({ PositionComponentId, ScaleComponentId })));
		e2->Add<ScaleComponent>(Vector3f(0.0f, 5.0f, 2.0f));
		PrintData(coll);
		coll.DestroyEntity(e);
		coll.DestroyEntity(e2);
		PrintData(coll);
	}
	coll.DestroyAllEntities();
	PrintData(coll);
	while (true);
}

void PrintData(EntityCollection& c) {
	cout << "------------------------------------------------" << endl;
	cout << "Entities:              " << c.CountOfEntities() << endl;
	cout << "Resusable Entities:    " << c.CountOfResuseableEntities() << endl;
	cout << "Retained Entities:     " << c.CountOfRetainedEntities() << endl;
	cout << "Resusable Components:  " << c.CountOfResuseableComponents() << endl;
}