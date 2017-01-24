#pragma once
#include "../../pch.h"
#include "Renderable.h"
#include "Camera.h"

using namespace System::Windows;
using namespace System::Windows::Controls;

namespace DesignerLib {

	class InternOpenGL;

	///Wrapper for InternOpenGL-Class
	/**
	* Führt die Methoden der InternOpenGL-Klasse
	* aus, damit diese in C# verwendet werden kann,
	* obwohl sie C++ features verwendet.
	*/
	public ref class OpenGL {
	private:
		InternOpenGL* m_gl;
	public:
		OpenGL();
		~OpenGL();

		void Initialize(double width, double height, Renderable^ r, DesignerLib::Camera^ cam);
		void ChangeSize(Size^ size);
		void Update(Renderable^ renderable);
		void Render(Image^ image);
	};
}