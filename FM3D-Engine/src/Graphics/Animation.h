#pragma once
#include <Engine.h>

namespace ENGINE_NAME {

	class Animation {
	private:
		Array<Array<Matrix4f>> m_bones;
		std::string m_name;
		Array<double> m_times;
		double m_keysPerSecond;
		double m_duration;
		friend class ExternFileManager;
	public:
		Animation(std::string, RawArray<Array<Matrix4f>>&, RawArray<double>&, double, double);

		inline const Matrix4f& GetBone(int bone, int key) const {
			return m_bones[bone][key];
		}

		RawArray<Matrix4f> GetBonePositions(double runningTime, const Array<Matrix4f>& offsetMatrices) const;
	};
}