#pragma once
#include"pch.h"

using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;

namespace DesignerLib {

	ref class ResourceReference;

	public ref class FoundResource : INotifyPropertyChanged {
	public:
		enum class Type {
			Unknown,
			Mesh,
			MeshPart,
			Animation,
			Texture,
			Material,
			Skeleton,
		};

		property bool Selected;
		property System::String^ Name;
		property System::String^ Path;
		property Type^ ResType;
		property ObservableCollection<ResourceReference^>^ References;

		FoundResource(std::string name, std::string path, Type^ type);
		FoundResource();

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}
	};

	public ref class ResourceReference {
	private:
		bool _Active;
	public:
		property FoundResource^ Parent;
		property FoundResource^ Reference;

		property bool Active {
			bool get() {
				return _Active;
			}
			void set(bool value) {
				_Active = value;
			}
		}
		property bool Available {
			bool get() {
				return Reference->Selected;
			}
		}
		property System::String^ Name {
			System::String^ get() {
				return Reference->Name;
			}
		}

		ResourceReference(FoundResource^ parent, FoundResource^ ref);
	};
}