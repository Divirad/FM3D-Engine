#include <Engine.h>

using namespace FM3D;
using namespace std;

class PositionComponent : public Component {
public:
	Vector3f position;
};

void PrintData(EntityCollection& c);

int main() {

	EntityCollection coll;
	EntityPtr e = coll.CreateEntity();
	e->Add<PositionComponent>();

	while (true);
}

void PrintData(EntityCollection& c) {
	cout << "------------------------------------------------" << endl;
	cout << "Entities:				" << c.CountOfEntities() << endl;
	cout << "Resusable Entities:	" << c.CountOfResuseableEntities() << endl;
	cout << "Retained Entities:		" << c.CountOfRetainedEntities() << endl;
	cout << "Resusable Components:	" << c.CountOfResuseableComponents() << endl;
}