#include <Engine.h>

namespace FM3D {

	Animation::Animation(std::string name, std::vector<std::vector<Matrix4f>>& bones, std::vector<double>& times, double keysPerSecond, double duration) :
		m_bones(bones), m_name(name), m_times(times), m_keysPerSecond(keysPerSecond), m_duration(duration) {

	};

	std::vector<Matrix4f> Animation::GetBonePositions(double runningTime, const std::vector<Matrix4f>& offsetMatrices) const {
		runningTime = fmod(runningTime, m_duration);
		if (runningTime < 0.0) return GetBonePositions(0.0, offsetMatrices);
		if (runningTime >= m_times[m_times.size()-1]) {	//No interpolation
			std::vector<Matrix4f> result(m_bones.size());
			uint numKeys = m_bones[0].size();
			for (uint b = 0; b < m_bones.size(); b++) {
				result[b] = m_bones[b][numKeys-1];
			}
			Matrix4f::MassMultiplication(result, offsetMatrices);
			return result;
		}

		std::vector<Matrix4f> result(m_bones.size());
		uint time = 0;
		for (; m_times[time] <= runningTime; time++);
		for (uint b = 0; b < m_bones.size(); b++) {
			result[b] = Matrix4f::Interpolate(m_bones[b][time - 1], m_bones[b][time], m_times[time - 1], runningTime, m_times[time]);
		}
		Matrix4f::MassMultiplication(result, offsetMatrices);
		return result;
	}
}