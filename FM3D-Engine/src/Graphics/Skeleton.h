#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class Skeleton {
	private:
		Array<Matrix4f> m_boneOffsetMatrices;
		Array<Animation> m_animations;
	public:
		Skeleton(RawArray<Matrix4f>& boneOffsetMatrices, RawArray<Animation>& animations);

		const Array<Matrix4f>& GetOffsetMatrices() const;
		const Array<Animation>& GetAnimations() const;
	};
}