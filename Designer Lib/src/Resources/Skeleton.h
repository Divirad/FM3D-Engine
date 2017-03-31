#pragma once
#define NO_FM3D
#include "ResourceRef.h"
#include "InternSkeleton.h"
#include "../pch.h"

namespace FM3D {
	class Skeleton;
}

using namespace System::Collections::ObjectModel;

namespace DesignerLib {

	public ref class Bone {
	public:
		property System::String^ position;
		property System::String^ rotation;
		property System::String^ scale;

		Bone(System::String^ p, System::String^ r, System::String^ s) {
			position = p;
			rotation = r;
			scale = s;
		}
	};

	public ref class Skeleton {
	private:
		InternSkeleton* m_skeleton;
	public:
		property bool IsSaved;

		property ObservableCollection<Bone^>^ Bones {
			ObservableCollection<Bone^>^ get() {
				auto result = gcnew ObservableCollection<Bone^>();
				auto bones = m_skeleton->GetBones();
				for (const auto& b : bones) {
					result->Add(gcnew Bone(ConvertString(b.position), ConvertString(b.rotation), ConvertString(b.scale)));
				}
				return result;
			}
		}

		property unsigned int BoneCount {
			unsigned int get() {
				return m_skeleton->GetBoneCount();
			}
		}
		property System::String^ Name;
		property System::String^ Path;
		property unsigned int Id;

		Skeleton(System::String^ name, System::String^ path, InternSkeleton* skeleton);

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