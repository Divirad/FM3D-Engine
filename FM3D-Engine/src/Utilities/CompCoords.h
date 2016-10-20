#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class ENGINE_DLL CompCoords
	{
	private:
		static Matrix4f s_matPixelToScreenSpace;
		static Matrix4f s_matScreenSpaceToPixel;
		//Vector2f vec;

	public:
		static void Initialize(int windowWidth, int windowHeigth);
		static Vector2f PixelToScreenSpace(Vector2f &pixel);
		static void ScalePixelToScreenSpace(Vector2f& pixel);
		static Vector2f ScreenSpaceToPixel(Vector2f &pixel);
		static void OnSizeChange(Window::SizeChangeEvent* sce);
	};

}