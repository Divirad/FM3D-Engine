#pragma once

#include "../Dll.h"
#ifdef NO_FM3D
namespace FM3D {
 struct MeshPart;
}
#else
#include <Engine.h>
#endif
#include <vector>

namespace DesignerLib {

	struct InternVertex {
		std::string position;
		std::string texCoord;
		std::string normal;
		std::string color;
		std::string boneIndex;
		std::string boneWeight;
		std::string tangent;
	};

	class InternMeshPart {
		FM3D::MeshPart* m_part;

	public:
		InternMeshPart(FM3D::MeshPart* part);

		std::vector<InternVertex>* GetVertices();
	};
}