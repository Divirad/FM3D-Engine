#include "ExternFileLoader.h"
#include <stdexcept>
#include <FreeImage.h>

namespace DesignerLib {

	array<System::Byte>^ ExternFileLoader::LoadTexture(System::String^ path, [Out] int% width, [Out] int% height) {

		System::IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(path);
		char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(nativeString, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(nativeString);
		if (fif == FIF_UNKNOWN) {
			throw std::runtime_error(static_cast<char*>((Marshal::StringToHGlobalAnsi(("Could not load texture: " + path)).ToPointer())));
		}

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, nativeString);

		if (dib == nullptr) {
			throw std::runtime_error(static_cast<char*>((Marshal::StringToHGlobalAnsi(("Could not load texture: " + path)).ToPointer())));
		}

		//MessageBox(hWnd, filename, "Could not load image '", MB_OK);

		BYTE* pixels = FreeImage_GetBits(dib);
		unsigned int w = FreeImage_GetWidth(dib);
		unsigned int h = FreeImage_GetHeight(dib);
		unsigned int bits = FreeImage_GetBPP(dib);

		width = (int)w;
		height = (int)h;

		int size = w * h * (bits / 8);
		array<System::Byte>^ result = gcnew array<System::Byte>(size);
		Marshal::Copy(System::IntPtr((void*)pixels), result, 0, size);
		FreeImage_Unload(dib);
		return result;
	}

}