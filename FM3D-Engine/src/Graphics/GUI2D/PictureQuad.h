#pragma once
#include <Engine.h>
namespace ENGINE_NAME {

	class ENGINE_DLL PictureQuad : public BasicItem2D {
	
	public:
		PictureQuad(Texture* txt, Vector3f pos0);
		PictureQuad(Texture* txt, Vector3f pos0, Vector2f pos1);
		PictureQuad(Texture* txt, Vector3f pos0, Vector2f pos1, uint color);
	};
}