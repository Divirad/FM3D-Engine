#ifdef EXPORT_DESIGNER_DLL
#define DESIGNER_DLL __declspec(dllexport)
#define DESIGNER_DLL_EXTERNTYPE
#else	
#define DESIGNER_DLL __declspec(dllimport)
#define DESIGNER_DLL_EXTERNTYPE extern
#endif