#pragma once
#include <Engine.h>
namespace ENGINE_NAME {

	class ENGINE_DLL Button : public BasicItem2D {

	private:
		bool animation;

		Vector3f mouse;

	public:
		Button(uint p_color, float p_koordx, float p_koordy, float p_sizex, float p_sizey, float p_z);

		Button(uint p_color, Texture *p_texture, Vector3f p_koord, Vector2f p_size);
		Button(uint p_color, Texture *p_texture, float p_koordx, float p_koordy, float p_sizex, float p_sizey, float p_z);

		Button(Texture* p_texture, Vector2f p_koord);
	};
}
