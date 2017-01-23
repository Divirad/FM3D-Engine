#include "InternMesh.h"

using namespace FM3D;

namespace DesignerLib {

	InternMeshPart::InternMeshPart(FM3D_MeshPart * part) {
	}

	std::vector<std::string>* InternMeshPart::GetVerticesStrings() {
		return new std::vector<std::string>();
	}
}