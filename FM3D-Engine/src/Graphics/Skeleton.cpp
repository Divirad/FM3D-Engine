#include <Engine.h>

namespace ENGINE_NAME {

	Skeleton::Skeleton(SharedArray<Matrix4f>& boneOffsetMatrices, SharedArray<Animation>& animations): m_boneOffsetMatrices(boneOffsetMatrices), m_animations(animations) {

	}

	const Array<Matrix4f>& Skeleton::GetOffsetMatrices() const {
		return m_boneOffsetMatrices;
	}

	const Array<Animation>& Skeleton::GetAnimations() const {
		return m_animations;
	}
}