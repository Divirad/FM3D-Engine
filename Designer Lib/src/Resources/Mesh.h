#pragma once

namespace FM3D {
	class Mesh;
}
#define NO_FM3D
#include "InternMesh.h"
#include "Skeleton.h"
#include "ResourceRef.h"

using namespace System::Collections::ObjectModel;
using namespace System::ComponentModel;

namespace DesignerLib {

	using StringCollection = System::Collections::ObjectModel::ObservableCollection<System::String^>^;
	ref class ExternResource;

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
		System::String^ name;
	public:

		property System::String^ Name {
			System::String^ get() {
				return name;
			}
			void set(System::String^ value) {
				if (value != name) {
					name = value;
					OnPropertyChanged("Name");
				}
			}
		}

		[System::ComponentModel::BrowsableAttribute(false)]
		property bool Visible;

		void SetVisibility(bool vis) {
			this->Visible = vis;
			OnPropertyChanged("Visible");
		}

		[DisplayName("Supports Instancing")]
		[Description("If true, multiple models with this mesh can be rendered with one drawcall for better performance")]
		property bool SupportsInstancing;

		[Category("Vertex data")]
		[DisplayName("Position")]
		[Description("If true, every vertex has a 3D position. Adds 12 bytes to the vertex size")]
		property bool HasPositionData {
			bool get() {
				return m_part->HasPositionData();
			}
		}

		[Category("Vertex data")]
		[DisplayName("Texture Coordinates")]
		[Description("If true, every vertex has a 2D texture coordinate so a texture can be mapped on the mesh-part. Adds 8 bytes to the vertex size")]
		property bool HasTexCoordData {
			bool get() {
				return m_part->HasTexCoordData();
			}
		}


		[Category("Vertex data")]
		[DisplayName("Normal")]
		[Description("If true, every vertex has a 3D normal vector for lightning calculations. Adds 12 bytes to the vertex size")]
		property bool HasNormalData {
			bool get() {
				return m_part->HasNormalData();
			}
		}

		[Category("Vertex data")]
		[DisplayName("Color")]
		[Description("If true, every vertex has a color. Adds 16 bytes to the vertex size")]
		property bool HasColorData {
			bool get() {
				return m_part->HasColorData();
			}
		}

		[Category("Vertex data")]
		[DisplayName("Bone data")]
		[Description("If true, every vertex has a bone index and a bone weight, so the mesh supports skeletal animation. Adds 32 bytes to the vertex size")]
		property bool HasBoneData {
			bool get() {
				return m_part->HasBoneData();
			}
		}

		[Category("Vertex data")]
		[DisplayName("Tangent")]
		[Description("If true, every vertex has a 3D tangent vector, so the mesh part supports normal mapping. Adds 12 bytes to the vertex size")]
		property bool HasTangentData {
			bool get() {
				return m_part->HasTangentData();
			}
		}

		MeshPart(System::String^ name, bool vis, InternMeshPart* part);
		~MeshPart();

		[System::ComponentModel::BrowsableAttribute(false)]
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

		InternMeshPart* GetIntern() { return m_part; }

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;
	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(name));
		}

		StringCollection Conv(std::vector<std::string>* str);
	};

	public ref class Mesh : System::ComponentModel::INotifyPropertyChanged {
	public:
		property bool IsSaved;

		property ObservableCollection<MeshPart^>^ Parts;
		property RefSkeleton^ Skelet;
		property System::String^ Name;
		property System::String^ Path;
		property unsigned int Id;
		property bool SupportsInstancing {
			bool get() {
				for each(auto p in Parts) {
					if (!p->SupportsInstancing) return false;
				}
				return true;
			}
		}

		Mesh(ObservableCollection<MeshPart^>^ parts, RefSkeleton^ skeleton, System::String^ name, System::String^ path);

		void RemovePart(MeshPart^ part) {
			if (Parts->Remove(part)) {
				OnPropertyChanged("Parts");
			}
		}

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;

		void WriteToFile();
		void ExportToFile();

		static Mesh^ FromFile(System::String^ path);
	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(name));
		}

		void OnPartChanged(System::Object^ sender, System::ComponentModel::PropertyChangedEventArgs^ e);
	};

	public ref class RefMesh : ResourceRef {
	public:
		property Mesh^ Target {
			Mesh^ get() {
				if (!IsLoaded) Load();
				return (Mesh^) m_target->Target;
			}
		}
		RefMesh(System::String^ path);
		RefMesh(Mesh^ mesh);
	private:
		void OnMeshChanged(System::Object^ sender, System::ComponentModel::PropertyChangedEventArgs^ e);
		void Load();
	};
}