#pragma once
#include <Engine.h>
#define DRAGGING true
#define DROPPED false

namespace FM3D {

	class ENGINE_DLL DragDropper : public Button {
	protected:
		Vector2f click, diff, size, mousepos;
		
	public:
		DragDropper(Texture* txt, Vector3f pos0) : Button(txt, pos0) {}
		DragDropper(Texture* txt, Vector3f pos0, Vector2f pos1) : Button(txt, pos0, pos1){}
		DragDropper(Texture* txt, Vector3f pos0, Vector2f pos1, uint color) : Button (txt, pos0, pos1, color){}
		DragDropper(Texture* txt, Vector3f pos0, Vector2f pos1, uint color, bool animation) : Button(txt, pos0, pos1, color, animation) {}

		bool DragDrop(int keyID);
		bool FollowMouse(int keyID);
	};
}