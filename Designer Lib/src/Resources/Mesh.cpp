#include "Mesh.h"
#include <vector>
#include "../pch.h"

using namespace System::Collections::ObjectModel;
using namespace System;
using namespace std;

namespace DesignerLib {

	Vertex::Vertex(const InternVertex* v) {
		this->Position = v->position.empty() ? nullptr : ConvertString(v->position);
		this->TexCoord = v->texCoord.empty() ? nullptr : ConvertString(v->texCoord);
		this->Normal = v->normal.empty() ? nullptr : ConvertString(v->normal);
		this->Color = v->color.empty() ? nullptr : ConvertString(v->color);
		this->BoneIndex = v->boneIndex.empty() ? nullptr : ConvertString(v->boneIndex);
		this->BoneWeight = v->boneWeight.empty() ? nullptr : ConvertString(v->boneWeight);
		this->Tangent = v->tangent.empty() ? nullptr : ConvertString(v->tangent);
	}

	MeshPart::MeshPart(System::String^ name, bool vis, FM3D::MeshPart* part) {
		this->Name = name;
		this->Visible = vis;
		m_part = new InternMeshPart(part);
	}

	ObservableCollection<String^>^ MeshPart::Conv(vector<string>* str) {
		if (str == nullptr) return nullptr;
		auto coll = gcnew ObservableCollection<String^>();
		for (const auto& s : *str) {
			coll->Add(ConvertString(s));
		}
		return coll;
	}

	Mesh::Mesh(ObservableCollection<MeshPart^>^ parts, Skeleton^ skeleton) {
		this->Parts = gcnew ObservableCollection<MeshPart^>();
		for each(auto p in parts) {
			this->Parts->Add(p);
		}
		this->skeleton = skeleton;
	}

}