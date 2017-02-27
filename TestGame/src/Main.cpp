#include <Engine.h>
#include <chrono>
#include <iomanip>

using namespace FM3D;
using namespace std;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	Matrix4f mat0 = Matrix4f::Transformation(Vector3f(2.0f, 1.0f, 3.0f), Vector3f(1.0f, 2.0f, 1.0f), Vector3f(30.0f, 10.0f, 5.0f));
	Quaternionf quat = Quaternionf::Rotation(30.0f, 10.0f, 5.0f);
	Transformation trans = Transformation::FromMatrix(mat0);

	cout << trans << endl << trans.rotation.Length() << endl << quat << endl;
	while (true);
}