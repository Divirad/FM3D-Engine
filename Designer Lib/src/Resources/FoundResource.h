#pragma once
#include <string>

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

		property System::String^ Name;
		property System::String^ Path;
		property Type^ ResType;
		property ObservableCollection<FoundResource^>^ Content;
		property bool IsReference;
		property FoundResource^ Parent;
		property FoundResource^ Reference;

		FoundResource(std::string name, std::string path, Type^ type);
		FoundResource(FoundResource^ parent, FoundResource^ reference);
		FoundResource();

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}
	};
}