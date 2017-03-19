#pragma once
#include <Engine.h>
#define MOUSE_INFIELD true
#define MOUSE_OUTOFFIELD false
#define INFIELDANIM 0.05f

namespace FM3D {

	class ENGINE_DLL Button : public BasicItem2D {
	public:

		
	protected:
		FIELDCHECK ifinfield;
		Input::KEYCLICK clicked;
		bool animate;

	public:

		Button(Texture* txt, Vector3f pos0);
		Button(Texture* txt, Vector3f pos0, Vector2f pos1);
		Button(Texture* txt, Vector3f pos0, Vector2f pos1, uint color);
		Button(Texture* txt, Vector3f pos0, Vector2f pos1, uint color, bool animation);

		inline void SetAnimation(bool anim) { animate = anim; }
		void Animation(bool in, float animsize);
		bool InFieldAnimation();
		bool InFieldAnimation(float animsize);
		bool ClickAnimation(int keyID);
	};
}
