#include <FreeImage.h>

using namespace System::Runtime::InteropServices;

public ref class ExternFileLoader {
public:
	static array<System::Byte>^ LoadTexture(System::String^ path, [Out] int% width, [Out] int% height);
};