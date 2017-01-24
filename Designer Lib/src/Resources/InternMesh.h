#pragma once

#ifdef NO_FM3D
namespace DesignerLib {
class FM3D_MeshPart;
}
namespace std {
	template<class T>
	class vector;

	class string;
}
#else
#include <Engine.h>
namespace DesignerLib {
	using FM3D_MeshPart = FM3D::Mesh::Part;
}
#endif

namespace DesignerLib {

	class InternMeshPart {
		FM3D_MeshPart* m_part;

		InternMeshPart(FM3D_MeshPart* part);

		std::vector<std::string>* GetVerticesStrings();
	};
}