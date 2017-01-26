#pragma once

namespace FM3D {
	class Mesh;
}
#define NO_FM3D
#include "InternMesh.h"

namespace DesignerLib {

	using StringCollection = System::Collections::ObjectModel::ObservableCollection<System::String^>^;

	public ref class Vertex {
	public:
		Vertex(const InternVertex* v);

		property System::String^ Position;
		property System::String^ TexCoord;
		property System::String^ Normal;
		property System::String^ Color;
		property System::String^ BoneIndex;
		property System::String^ BoneWeight;
		property System::String^ Tangent;
	};

	public ref class MeshPart : System::ComponentModel::INotifyPropertyChanged {
	private:
		InternMeshPart* m_part;
	public:
		property System::String^ Name;
		property bool Visible;

		MeshPart();

		void SetName(System::String^ name) {
			this->Name = name;
			OnPropertyChanged("Name");
		}

		void SetVisibility(bool vis) {
			this->Visible = vis;
			OnPropertyChanged("Visible");
		}

		MeshPart(System::String^ name, bool vis) {
			this->Name = name;
			this->Visible = vis;
		}

		property System::Collections::ObjectModel::ObservableCollection<Vertex^>^ Vertices {
			System::Collections::ObjectModel::ObservableCollection<Vertex^>^ get() {
 				auto vec = m_part->GetVertices();
				if (vec == nullptr) return nullptr;
				auto coll = gcnew System::Collections::ObjectModel::ObservableCollection<Vertex^>();
				for (const auto& v : *vec) {
					coll->Add(gcnew Vertex(&v));
				}
				return coll;
			}
		}

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;
	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(name));
		}

		StringCollection Conv(std::vector<std::string>* str);
	};

	public ref class Mesh : System::ComponentModel::INotifyPropertyChanged {
	public:
		property System::Collections::ObjectModel::ObservableCollection<MeshPart^>^ Parts;

		Mesh() {
			this->Parts = gcnew System::Collections::ObjectModel::ObservableCollection<MeshPart^>();
			this->Parts->Add(gcnew MeshPart("Halllo 1", false));
			this->Parts->Add(gcnew MeshPart("Byebye 2", true ));
		}

		void RemovePart(MeshPart^ part) {
			if (Parts->Remove(part)) {
				OnPropertyChanged("Parts");
			}
		}

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;
	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(name));
		}
	};
}