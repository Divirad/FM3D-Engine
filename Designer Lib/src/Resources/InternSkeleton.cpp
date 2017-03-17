#include "InternSkeleton.h"

namespace DesignerLib {

	InternSkeleton::InternSkeleton(FM3D::Skeleton* skeleton) : m_skeleton(skeleton) {
	}

	unsigned int InternSkeleton::GetBoneCount() {
		return m_skeleton->GetOffsetMatrices().size();
	}

	void InternSkeleton::WriteToFile(std::ofstream& file) {
		file.write(reinterpret_cast<const char*>(&m_skeleton->GetOffsetMatrices()), m_skeleton->GetOffsetMatrices().size() * sizeof(FM3D::Matrix4f));
	}

	InternSkeleton* InternSkeleton::FromFile(std::ifstream& file) {
		return nullptr;
	}
}
