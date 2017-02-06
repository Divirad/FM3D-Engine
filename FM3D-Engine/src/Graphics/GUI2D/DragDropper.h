#pragma once
#include <Engine.h>
#define DRAGGING true
#define DROPPED false

namespace FM3D {

	class ENGINE_DLL DragDropper : public Button {
	protected:
		Vector2f click, diff, size, mousepos;
		
	public:
		DragDropper(Texture* txt, Vector3f pos0) : Button(txt, pos0), 
			click(Vector2f::Zero()), diff(Vector2f::Zero()), size(Vector2f::Zero()), mousepos(Vector2f::Zero()) {}
		DragDropper(Texture* txt, Vector3f pos0, Vector2f pos1) : Button(txt, pos0, pos1),
			click(Vector2f::Zero()), diff(Vector2f::Zero()), size(Vector2f::Zero()), mousepos(Vector2f::Zero()) {}
		DragDropper(Texture* txt, Vector3f pos0, Vector2f pos1, uint color) : Button (txt, pos0, pos1, color),
			click(Vector2f::Zero()), diff(Vector2f::Zero()), size(Vector2f::Zero()), mousepos(Vector2f::Zero()) {}
		DragDropper(Texture* txt, Vector3f pos0, Vector2f pos1, uint color, bool animation) : Button(txt, pos0, pos1, color, animation),
			click(Vector2f::Zero()), diff(Vector2f::Zero()), size(Vector2f::Zero()), mousepos(Vector2f::Zero()) {}

		bool DragDrop(int keyID);
		bool FollowMouse(int keyID);
	};
}