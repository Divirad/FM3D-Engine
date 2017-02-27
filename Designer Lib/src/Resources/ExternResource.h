#pragma once
#define NO_FM3D
#include "../pch.h"
#include "FoundResource.h"
#pragma managed(push, off)
#include "ResourceLoader.h"
#pragma managed(pop)
#include "Mesh.h"
#include "Skeleton.h"

using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace DesignerLib {

	ref class Mesh;

	public ref class ExternResource : INotifyPropertyChanged {
	private:
		ResourceLoader* m_loader;
		Dictionary<FoundResource^, uint>^ m_meshPartMap;
	public:
		property ObservableCollection<FoundResource^>^ Resources;
		property IResourceContainer^ Master;

		ExternResource();
		~ExternResource();
		void Load(System::String^ path);

		virtual event PropertyChangedEventHandler^ PropertyChanged;

		ObservableCollection<Mesh^>^ GetMeshes(Skeleton^ skeleton);
		Skeleton^ GetSkeleton();

		ObservableCollection<Mesh^>^ CreateAll([Out] Skeleton^% skeleton);

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}
	};
}