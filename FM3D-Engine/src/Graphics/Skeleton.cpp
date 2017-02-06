#include <Engine.h>

namespace FM3D {

	Skeleton::Skeleton(std::vector<Matrix4f>& boneOffsetMatrices, std::vector<Animation>& animations): m_boneOffsetMatrices(boneOffsetMatrices), m_animations(animations) {

	}

	const std::vector<Matrix4f>& Skeleton::GetOffsetMatrices() const {
		return m_boneOffsetMatrices;
	}

	const std::vector<Animation>& Skeleton::GetAnimations() const {
		return m_animations;
	}
}