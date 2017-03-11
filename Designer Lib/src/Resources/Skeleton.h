#pragma once

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
		FM3D::Skeleton* m_skeleton;
	public:
		property int BoneCount;
		property System::String^ Name;
		property unsigned int Id;

		Skeleton(int boneCount, System::String^ name, FM3D::Skeleton* skeleton) {
			this->m_skeleton = skeleton;
			this->BoneCount = boneCount;
			this->Name = name;
			this->Id = 0xffffffff;
		}

		FM3D::Skeleton* GetIntern() { return m_skeleton; }
	};
}