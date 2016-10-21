#pragma once
#include <Engine.h>
#define MOUSE_INFIELD true
#define MOUSE_OUTOFFIELD false

namespace ENGINE_NAME {

	class ENGINE_DLL Button : public BasicItem2D {
	public:

		enum FieldCheck {
			INFIELD,
			ALREADY_INFIELD,
			OUTFIELD,
			ALREADY_OUTFIELD
		};

	private:
		FieldCheck ifinfield;
		bool animate;

	public:

		Button(Texture* txt, Vector3f pos0);
		Button(Texture* txt, Vector3f pos0, Vector2f pos1);
		Button(Texture* txt, Vector3f pos0, Vector2f pos1, uint color);
		Button(Texture* txt, Vector3f pos0, Vector2f pos1, uint color, bool animation);

		inline void SetAnimation(bool animation) { animate = animation; }
		void Animation(FieldCheck isin);
		void Animation(FieldCheck isin, float animsize);
		bool InFieldAnimation();

	};
}
