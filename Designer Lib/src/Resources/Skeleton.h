#pragma once
#define NO_FM3D
#include "ResourceRef.h"
#include "InternSkeleton.h"

namespace FM3D {
	class Skeleton;
}

using namespace System::Collections::ObjectModel;

namespace DesignerLib {

	public ref class Bone {
	public:
		property ObservableCollection<Bone^>^ Children;
		property System::String^ Name;
	};

	public ref class Skeleton {
	private:
		InternSkeleton* m_skeleton;
	public:
		property unsigned int BoneCount {
			unsigned int get() {
				return m_skeleton->GetBoneCount();
			}
		}
		property System::String^ Name;
		property System::String^ Path;
		property unsigned int Id;

		Skeleton(System::String^ name, System::String^ path, InternSkeleton* skeleton) {
			this->m_skeleton = skeleton;
			this->Name = name;
			this->Id = 0xffffffff;
			this->Path = path;
		}

		FM3D::Skeleton* GetIntern() { return m_skeleton->GetIntern(); }

		void WriteToFile();
		void ExportToFile();

		static Skeleton^ FromFile(System::String^ path);

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;
	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(name));
		}
	};

	public ref class RefSkeleton : ResourceRef {
	public:
		property Skeleton^ Target {
			Skeleton^ get() {
				if (!IsLoaded) Load();
				return (Skeleton^)m_target->Target;
			}
		}
		RefSkeleton(System::String^ path);
		RefSkeleton(Skeleton^ skel);
	private:
		void OnSkelChanged(System::Object^ sender, System::ComponentModel::PropertyChangedEventArgs^ e);
		void Load();
	};
}