#pragma once
#include "../pch.h"
#include "FoundResource.h"
#include <Assimp/Importer.hpp>
#include <Assimp/scene.h>
#include <Assimp/postprocess.h>

using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;

namespace DesignerLib {

	public ref class ExternResource : INotifyPropertyChanged {
	private:
		Assimp::Importer* importer;
		const aiScene* scene;
	public:
		property ObservableCollection<FoundResource^>^ Resources;
		property IResourceContainer^ Master;

		ExternResource();
		~ExternResource();
		void Load(System::String^ path);

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}
	};
}