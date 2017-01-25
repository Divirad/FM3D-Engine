#pragma once

#include "../Dll.h"
#ifdef NO_FM3D
namespace DesignerLib {
class FM3D_MeshPart;
}
#else
#include <Engine.h>
namespace DesignerLib {
	using FM3D_MeshPart = FM3D::Mesh::Part;
}
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
		FM3D_MeshPart* m_part;

	public:
		InternMeshPart(FM3D_MeshPart* part);
		InternMeshPart() {};

		std::vector<InternVertex>* GetVertices();
	};
}