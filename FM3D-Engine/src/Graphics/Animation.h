#pragma once
#include <Engine.h>

namespace FM3D {

	class Animation {
	private:
		std::vector<std::vector<Transformation>> m_bones;
		std::string m_name;
		std::vector<double> m_times;
		double m_keysPerSecond;
		double m_duration;
		friend class ExternFileManager;
	public:
		Animation(std::string, const std::vector<std::vector<Transformation>>&, std::vector<double>&, double, double);

		inline const Transformation& GetBone(int bone, int key) const {
			return m_bones[bone][key];
		}

		std::vector<Matrix4f> GetBonePositions(double runningTime, const std::vector<Matrix4f>& offsetMatrices) const;
		double GetDuration() const { return m_duration; }
	};
}