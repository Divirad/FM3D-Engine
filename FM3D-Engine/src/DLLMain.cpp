#include <Engine.h>


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
#ifdef _DEBUG
	OutputDebugString(L"Engine dll loaded!\n");
	_CrtSetDbgFlag(_CRTDBG_CHECK_ALWAYS_DF);
#endif

	return TRUE;
}