#pragma once
#include <Engine.h>

namespace FM3D {

	class ENGINE_DLL Skeleton {
	private:
		std::vector<Matrix4f> m_boneOffsetMatrices;
		std::vector<Animation> m_animations;
	public:
		Skeleton(std::vector<Matrix4f>& boneOffsetMatrices, std::vector<Animation>& animations);

		const std::vector<Matrix4f>& GetOffsetMatrices() const;
		const std::vector<Animation>& GetAnimations() const;
	};
}