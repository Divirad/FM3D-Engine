#pragma once
#include <Engine.h>

namespace FM3D {

	class Skeleton;

	class Animation {
	public:
		struct AnimatedBone {
			TimeList<Vector3f> position;
			TimeList<Quaternionf> rotation;
			TimeList<Vector3f> scale;
		};
		struct Bone {
			int index;
			int animation;
			std::vector<uint> children;

			inline bool IsAnimated() const { return index >= 0; }
		};
	private:
		int m_rootBone;
		std::vector<AnimatedBone> m_animBones;
		std::vector<Bone> m_bones;
		uint m_boneCount;
		
		std::string m_name;
		double m_keysPerSecond;
		double m_duration;
		const Skeleton* m_skeleton;

		friend class ExternFileManager;
	public:
		Animation(std::string name, const std::vector<Bone>& bones, const std::vector<AnimatedBone>& abones, int rootBone, double keysPerSecond, uint boneCount, const Skeleton* skeleton, AdvanceRule rule = REPEAT);
		Animation(std::string name, std::vector<Bone>&& bones, std::vector<AnimatedBone>&& abones, int rootBone, double keysPerSecond, uint boneCount, const Skeleton* skeleton, AdvanceRule rule = REPEAT);

		void SetAdvanceRule(AdvanceRule rule);

		std::vector<Matrix4f> GetBoneTransformations(double runningTime) const;
		double GetDuration() const { return m_animBones[0].position.End(); }
	private:
		void SetSameEnding();
		void ReadBoneHierarchy(double time, const Transformation& parentTransform, const Bone& bone, std::vector<Matrix4f>& result) const;
	};
}