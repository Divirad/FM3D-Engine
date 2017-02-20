#include <Engine.h>

namespace FM3D {

	//std::vector<Matrix4f> Animation::GetBoneTransformations(double runningTime, const std::vector<Matrix4f>& offsetMatrices) const {
	//	runningTime = fmod(runningTime, m_duration);
	//	if (runningTime < 0.0) return GetBoneTransformations(0.0, offsetMatrices);

	//	if (runningTime >= m_times[m_times.size()-1]) {	//No interpolation
	//		std::vector<Matrix4f> result(m_bones.size(), Matrix4f::Identity());
	//		uint numKeys = m_bones[0].size();
	//		for (uint b = 0; b < m_bones.size(); b++) {
	//			result[b] = m_bones[b][numKeys-1].ToMatrix();
	//		}

	//		for (uint i = 0; i < result.size(); i++) {
	//			result[i] *= offsetMatrices[i];
	//		}
	//		return result;
	//	}

	//	std::vector<Matrix4f> result(m_bones.size(), Matrix4f::Identity());
	//	uint time = 0;
	//	for (; m_times[time] <= runningTime; time++);
	//	for (uint b = 0; b < m_bones.size(); b++) {						
	//		result[b] = m_bones[b][time - 1].Interpolate(m_bones[b][time], (runningTime - m_times[time - 1]) / (m_times[time] - m_times[time - 1])).ToMatrix();
	//	}

	//	for (uint i = 0; i < result.size(); i++) {
	//		result[i] *= offsetMatrices[i];
	//	}
	//	return result;
	//}

	Animation::Animation(std::string name, const std::vector<Bone>& bones, const std::vector<AnimatedBone>& abones, int rootBone, double keysPerSecond, uint boneCount, const Skeleton * skeleton, AdvanceRule rule):
		m_name(name), m_bones(bones), m_animBones(abones), m_rootBone(rootBone), m_keysPerSecond(keysPerSecond), m_boneCount(boneCount), m_skeleton(skeleton) {
		SetAdvanceRule(rule);
		SetSameEnding();
	}
	 
	Animation::Animation(std::string name, std::vector<Bone>&& bones, std::vector<AnimatedBone>&& abones, int rootBone, double keysPerSecond, uint boneCount, const Skeleton * skeleton, AdvanceRule rule):
		m_name(name), m_bones(bones), m_animBones(abones), m_rootBone(rootBone), m_keysPerSecond(keysPerSecond), m_boneCount(boneCount), m_skeleton(skeleton) {
		SetAdvanceRule(rule);
		SetSameEnding();
	}

	void Animation::SetAdvanceRule(AdvanceRule rule) {
		for (size_t i = 0, s = m_animBones.size(); i < s; i++) {
			m_animBones[0].position.SetRule(rule);
			m_animBones[1].rotation.SetRule(rule);
			m_animBones[2].scale.SetRule(rule);
		}
	}

	std::vector<Matrix4f> Animation::GetBoneTransformations(double runningTime) const {
		runningTime = std::max(0.0, runningTime);

		std::vector<Matrix4f> result(m_boneCount, Matrix4f::Identity());
		ReadBoneHierarchy(runningTime, Transformation(), m_bones[m_rootBone], result);
		return result;
	}

	void Animation::SetSameEnding() {
		double maxTime = 0.0;
		for (size_t i = 0, s = m_animBones.size(); i < s; i++) {
			maxTime = std::max(maxTime, m_animBones[0].position.End());
			maxTime = std::max(maxTime, m_animBones[1].rotation.End());
			maxTime = std::max(maxTime, m_animBones[2].scale.End());
		}
		for (size_t i = 0, s = m_animBones.size(); i < s; i++) {
			m_animBones[0].position.SetEnd(maxTime);
			m_animBones[1].rotation.SetEnd(maxTime);
			m_animBones[2].scale.SetEnd(maxTime);
		}
	}

	void Animation::ReadBoneHierarchy(double time, const Transformation& parentTransform, const Bone& bone, std::vector<Matrix4f>& result) const {
		if (bone.IsAnimated()) {
			const AnimatedBone& anim = m_animBones[bone.animation];
			Transformation transform = parentTransform * Transformation(anim.position[time], anim.rotation[time], anim.scale[time]);

			if (bone.index >= 0) {
				result[bone.index] = transform.ToMatrix() * m_skeleton->GetOffsetMatrices()[bone.index];
			}

			for (int child : bone.children) {
				ReadBoneHierarchy(time, transform, m_bones[child], result);
			}
		}
		else {
			for (int child : bone.children) {
				ReadBoneHierarchy(time, parentTransform, m_bones[child], result);
			}
		}


	}
}