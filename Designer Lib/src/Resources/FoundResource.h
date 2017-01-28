#pragma once
#include <string>

using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;
using namespace System::Windows::Controls;

namespace DesignerLib {

	ref class ResourceReference;
	ref class FoundResource;
	ref class ExternResource;

	public enum class ResourceType {
		Unknown,
		Mesh,
		MeshPart,
		Animation,
		Texture,
		Material,
		Skeleton,
	};

	public interface class IResourceContainer {
	public:
		virtual void OnRemove(FoundResource^) = 0;
		virtual void OnDelete(FoundResource^) = 0;
		virtual void OnChangeMesh(FoundResource^) = 0;
	};

	public ref class FoundResource : INotifyPropertyChanged {
	public:

		property System::String^ Name;
		property System::String^ Path;
		property ResourceType ResType;
		property ObservableCollection<FoundResource^>^ Content;
		property bool IsReference;
		property FoundResource^ Parent;
		property FoundResource^ Reference;
		property ExternResource^ Master;

		property ContextMenu^ CMenu {
			ContextMenu^ get();
		}

		FoundResource(std::string name, std::string path, ResourceType type, ExternResource^ master);
		FoundResource(System::String^ name, System::String^ path, ResourceType type, ExternResource^ master);
		FoundResource(FoundResource^ parent, FoundResource^ reference, ExternResource^ master);
		FoundResource();

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}

		void OnResourcesChanged(Object^ sender, System::Collections::Specialized::NotifyCollectionChangedEventArgs^ e) {
			OnPropertyChanged("CMenu");
		}

		void OnRemove(Object^ sender, System::Windows::RoutedEventArgs^ e);
		void OnDelete(Object^ sender, System::Windows::RoutedEventArgs^ e);
		void OnChangeMesh(Object^ sender, System::Windows::RoutedEventArgs^ e);
	};
}