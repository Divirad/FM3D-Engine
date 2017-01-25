#include "Mesh.h"
#include <vector>
#include "../pch.h"

using namespace System::Collections::ObjectModel;
using namespace System;
using namespace std;

namespace DesignerLib {

	Vertex::Vertex(const InternVertex* v) {
		this->Position = ConvertString(v->position);
		this->TexCoord = ConvertString(v->texCoord);
		this->Normal = ConvertString(v->normal);
		this->Color = ConvertString(v->color);
		this->BoneIndex = ConvertString(v->boneIndex);
		this->BoneWeight = ConvertString(v->boneWeight);
		this->Tangent = ConvertString(v->tangent);
	}

	MeshPart::MeshPart() {
		m_part = new InternMeshPart();
	}

	ObservableCollection<String^>^ MeshPart::Conv(vector<string>* str) {
		if (str == nullptr) return nullptr;
		auto coll = gcnew ObservableCollection<String^>();
		for (const auto& s : *str) {
			coll->Add(ConvertString(s));
		}
		return coll;
	}

}