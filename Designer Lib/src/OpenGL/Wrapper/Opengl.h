#pragma once
#include "../../pch.h"
#include "Renderable.h"
#include "Camera.h"
#include "../../Resources/Mesh.h"

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

		Renderable^ Initialize(double width, double height, DesignerLib::Camera^ cam, Mesh^ mesh);
		void ChangeSize(Size^ size);
		void Update(Renderable^ renderable);
		void Render(Image^ image);
	};
}