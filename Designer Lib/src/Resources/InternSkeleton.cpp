#include "InternSkeleton.h"
#include "../FileWriting.h"

namespace DesignerLib {

	InternSkeleton::InternSkeleton(FM3D::Skeleton* skeleton) : m_skeleton(skeleton) {
	}

	std::vector<InternBone> InternSkeleton::GetBones() {
		std::vector<InternBone> result;
		for (const auto& m : m_skeleton->GetOffsetMatrices()) {
			auto t = FM3D::Transformation::FromMatrix(m);
			result.push_back(InternBone{ t.position.ToString(), t.rotation.ToAngles().ToString(), t.scale.ToString() });
		}
		return result;
	}

	unsigned int InternSkeleton::GetBoneCount() {
		return m_skeleton->GetOffsetMatrices().size();
	}

	void InternSkeleton::WriteToFile(std::ofstream& file) {
		file.write(reinterpret_cast<const char*>(&m_skeleton->GetOffsetMatrices()), m_skeleton->GetOffsetMatrices().size() * sizeof(FM3D::Matrix4f));
	}

	InternSkeleton* InternSkeleton::FromFile(std::ifstream& file, unsigned int boneCount) {
		std::vector<FM3D::Matrix4f> matrices;
		matrices.reserve(boneCount);
		for (FM3D::uint i = 0; i < boneCount; i++) {
			matrices.push_back(ReadRawFromFile<FM3D::Matrix4f>(file));
		}

		return new InternSkeleton(new FM3D::Skeleton(matrices, std::vector<FM3D::Animation>()));
	}
}
