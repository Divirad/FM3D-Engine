#pragma once
#include "pch.h"
#include "InternOpengl.h"

using namespace System::Windows;
using namespace System::Windows::Controls;

namespace DesignerLib {

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

		void Initialize(double width, double height);
		void ChangeSize(Size^ size);
		void Update();
		void Render(Image^ image);
	};
}