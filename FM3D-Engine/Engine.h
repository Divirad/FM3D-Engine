#pragma once

#include <src/pch.h>

#ifdef EXPORT_DLL
#define ENGINE_DLL __declspec(dllexport)
#define ENGINE_DLL_EXTERNTYPE
#else
#define ENGINE_DLL __declspec(dllimport)
#define ENGINE_DLL_EXTERNTYPE extern
#endif

#pragma warning(disable:4251)

#undef near
#undef far
#undef LoadImage

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ZERO_MEM(a) memset(a, 0, sizeof(a))

#define ALL_FM3D_NAMESPACES namespace FM3D; using namespace FM3D::EntitySystem;

namespace FM3D {

	using byte = unsigned char;
	using uint = unsigned int;
	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using int8 = char;
	using int16 = short;
	using int32 = int;

	enum Platform {
		WINDOWS
	};

	enum Renderer {
		OpenGL3_3,
		OpenGL4_5
	};
}

#include <src/Timer.h>
#include <src/Output.h>

#include <src/Memory/ArrayBase.h>
#include <src/Memory/DynamicArrayBase.h>
#include <src/Memory/DynamicRawArray.h>
#include <src/Memory/RawArray.h>
#include <src/Memory/Array.h>
#include <src/Memory/DynamicArray.h>

#include <src/Math/Math.h>

#include <src/Utilities/StringUtilities.h>
#include <src/EventSystem.h>

#include <src/WindowSystem/Input.h>
#include <src/WindowSystem/Window.h>
#include <src/WindowSystem/Win32Window.h>
#include <src/Utilities/CompCoords.h>

#include <src/EntitySystem/Event.h>
#include <src/EntitySystem/Component.h>
#include <src/EntitySystem/Matcher.h>
#include <src/EntitySystem/EntityCollection.h>
#include <src/EntitySystem/Group.h>
#include <src/EntitySystem/Entity.h>
#include <src/EntitySystem/EntityLogic.h>
#include <src/EntitySystem/ComponentArgs.h>

#include <src/BasicComponents.h>

#include <src/Graphics/TimeList.h>
#include <src/Graphics/Texture.h>
#include <src/Graphics/RenderTarget2D.h>
#include <src/Graphics/Quad.h>
#include <src/Graphics/Font.h>
#include <src/Graphics/Camera.h>
#include <src/Graphics/Lights.h>
#include <src/Graphics/Shader.h>
#include <src/Graphics/Animation.h>
#include <src/Graphics/Skeleton.h>
#include <src/Graphics/Material.h>
#include <src/Graphics/Vertices.h>
#include <src/Graphics/Mesh.h>
#include <src/Graphics/Model.h>
#include <src/Graphics/RenderableComponent.h>
#include <src/Graphics/Terrain.h>

//#include <src/Entity.h>

#include <src/Graphics/Renderer2D.h>
#include <src/Graphics/Renderer3D.h>
#include <src/Graphics/RenderSystem.h>

#include <src/Graphics/MeshCreator.h>

//2DRendering
//#include <src/Graphics/GUI2D/BasicItem2D.h>
//#include <src/Graphics/GUI2D/PictureQuad.h>
//#include <src/Graphics/GUI2D/TextQuad.h>
//#include <src/Graphics/GUI2D/Button.h>
//#include <src/Graphics/GUI2D/DragDropper.h>

//DirectX11
//#include <src/Graphics/D3D11/D3D11RenderSystem.h>
//#include <src/Graphics/D3D11/D3D11Shader.h>
//#include <src/Graphics/D3D11/D3D11Model.h>
//#include <src/Graphics/D3D11/D3D11Texture.h>

#include <src/Graphics/OpenGL3.3/GL3Mesh.h>
#include <src/Graphics/OpenGL3.3/GL3Texture.h>
#include <src/Graphics/OpenGL3.3/GL3RenderTarget2D.h>
#include <src/Graphics/OpenGL3.3/GL3Shader.h>
#include <src/Graphics/OpenGL3.3/2D/GL3Renderer2D.h>
#include <src/Graphics/OpenGL3.3/3D/GL3GBuffer.h>
#include <src/Graphics/OpenGL3.3/3D/GL3NullShader.h>
#include <src/Graphics/OpenGL3.3/3D/GL3LightShader.h>
#include <src/Graphics/OpenGL3.3/3D/GL3Shader3D.h>
#include <src/Graphics/OpenGL3.3/3D/GL3Renderer3D.h>
#include <src/Graphics/OpenGL3.3/3D/GL3Terrain.h>

#include <src/Graphics/OpenGL3.3/GL3RenderSystem.h>

//OpenGL4.4
#include <src/Graphics/OpenGL4.5/GL4Renderer2D.h>
#include <src/Graphics/OpenGL4.5/GL4RenderSystem.h>

#include <src/FileSystem/FileManager.h>
#include <src/FileSystem/ExternFileManager.h>