#include <Engine.h>
#include <chrono>
#include <iomanip>
#include "OldMatrix.h"

using namespace FM3D;
using namespace std;

static Matrix4f CreateMatrix4f(const aiMatrix4x4& mat) {
	Matrix4f result = Matrix4f::Null();
	result.elements[0] = mat.a1;
	result.elements[1] = mat.b1;
	result.elements[2] = mat.c1;
	result.elements[3] = mat.d1;
	result.elements[4] = mat.a2;
	result.elements[5] = mat.b2;
	result.elements[6] = mat.c2;
	result.elements[7] = mat.d2;
	result.elements[8] = mat.a3;
	result.elements[9] = mat.b3;
	result.elements[10] = mat.c3;
	result.elements[11] = mat.d3;
	result.elements[12] = mat.a4;
	result.elements[13] = mat.b4;
	result.elements[14] = mat.c4;
	result.elements[15] = mat.d4;
	result.Transpose();
	return result;
}
static Vector3f CreateVec(const aiVector3D& vec) {
	return Vector3f(vec.x, vec.y, vec.z);
}
static Matrix4f& CreateRealZero(Matrix4f& mat) {
	if(mat.elements[0]  == -0.0f) mat.elements[0]  = 0.0f;
	if(mat.elements[1]  == -0.0f) mat.elements[1]  = 0.0f;
	if(mat.elements[2]  == -0.0f) mat.elements[2]  = 0.0f;
	if(mat.elements[3]  == -0.0f) mat.elements[3]  = 0.0f;
	if(mat.elements[4]  == -0.0f) mat.elements[4]  = 0.0f;
	if(mat.elements[5]  == -0.0f) mat.elements[5]  = 0.0f;
	if(mat.elements[6]  == -0.0f) mat.elements[6]  = 0.0f;
	if(mat.elements[7]  == -0.0f) mat.elements[7]  = 0.0f;
	if(mat.elements[8]  == -0.0f) mat.elements[8]  = 0.0f;
	if(mat.elements[9]  == -0.0f) mat.elements[9]  = 0.0f;
	if(mat.elements[10] == -0.0f) mat.elements[10] = 0.0f;
	if(mat.elements[11] == -0.0f) mat.elements[11] = 0.0f;
	if(mat.elements[12] == -0.0f) mat.elements[12] = 0.0f;
	if(mat.elements[13] == -0.0f) mat.elements[13] = 0.0f;
	if(mat.elements[14] == -0.0f) mat.elements[14] = 0.0f;
	if(mat.elements[15] == -0.0f) mat.elements[15] = 0.0f;
	return mat;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	Matrix4f mat0 = Matrix4f::Transformation(Vector3f(2.0f, 1.0f, 3.0f), Vector3f(1.0f, 2.0f, 1.0f), Vector3f(30.0f, 10.0f, 5.0f));
	Quaternionf quat = Quaternionf::Rotation(30.0f, 10.0f, 5.0f);
	Transformation trans = Transformation::FromMatrix(mat0);

	cout << trans << endl << trans.rotation.Length() << endl << quat << endl;
	while (true);
}