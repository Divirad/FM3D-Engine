#pragma once

#include "../Dll.h"
#ifdef NO_FM3D
namespace FM3D {
	class Skeleton;
	class Animation;
}
#else
#include <Engine.h>
#endif
#include<fstream>
#include <vector>
#include <string>

namespace DesignerLib {

	struct InternBone {
		std::string position;
		std::string rotation;
		std::string scale;
	};
	
	class InternSkeleton {
	private:
		FM3D::Skeleton* m_skeleton;
	public:
		InternSkeleton(FM3D::Skeleton* skeleton);

		std::vector<InternBone> GetBones();

		FM3D::Skeleton* GetIntern() { return m_skeleton; }
		unsigned int GetBoneCount();

		void WriteToFile(std::ofstream& file);
		static InternSkeleton* FromFile(std::ifstream& file, unsigned int boneCount);
	};
}