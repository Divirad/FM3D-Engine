#include <Engine.h>

using namespace ENGINE_NAME;

#define OUTPUT(arr0) std::cout << "S: " << arr0.Size() << " C: " << arr0.Capacity() << " A: " << &arr0[0] << " SE: " << &arr0[arr0.Size()-1] << " CE: " << &arr0[arr0.Capacity() - 1] << std::endl;

void OUTPUTALL(const DynamicArrayBase<uint>& a) {
	uint i;
	for (i = 0u; i < a.Size(); i++) {
		std::cout << a[i] << " ";
	}
	std::cout << "-- ";
	for (; i < a.Capacity(); i++) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Window::StartConsole();

	DynamicRawArray<uint> arr0(5);

	for (uint i = 0u; i < arr0.Size(); i++) {
		arr0[i] = 77;
	}

	arr0[arr0.Size() - 1] = 3;
	arr0[arr0.Capacity() - 1] = 5;
	OUTPUT(arr0);
	OUTPUTALL(arr0);
	arr0.AdvanceCapBy(7);
	arr0[arr0.Size() - 1] = 3;
	arr0[arr0.Capacity() - 1] = 5;
	OUTPUT(arr0);
	OUTPUTALL(arr0);
	arr0.AdvanceBy(4);
	arr0[arr0.Size() - 1] = 3;
	arr0[arr0.Capacity() - 1] = 5;
	OUTPUT(arr0);
	OUTPUTALL(arr0);
	arr0.AdvanceBy(4);
	arr0[arr0.Size() - 1] = 3;
	arr0[arr0.Capacity() - 1] = 5;
	OUTPUT(arr0);
	OUTPUTALL(arr0);

	std::cout << std::endl;

	std::cout << std::endl;

	for (const uint& u : arr0) {
		std::cout << "  " << &u << std::endl;
	}

	std::cout << std::endl;

	while (true) {};
}