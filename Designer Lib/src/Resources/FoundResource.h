#pragma once
#include <string>

using namespace System::ComponentModel;
using namespace System::Collections::ObjectModel;
using namespace System::Windows::Controls;

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

		property ContextMenu^ CMenu {
			ContextMenu^ get() {
				auto menu = gcnew ContextMenu();

				if (*ResType == Type::MeshPart) {
					auto changeMesh = gcnew MenuItem();
					changeMesh->Click += gcnew System::Windows::RoutedEventHandler(this, &FoundResource::OnChangeMesh);
					menu->Items->Add(changeMesh);
				}
				if (IsReference) {
					auto remove = gcnew MenuItem();
					remove->Click += gcnew System::Windows::RoutedEventHandler(this, &FoundResource::OnRemove);
					menu->Items->Add(remove);
				}
				else {
					auto delet = gcnew MenuItem();
					delet->Click += gcnew System::Windows::RoutedEventHandler(this, &FoundResource::OnDelete);
					menu->Items->Add(delet);
				}
				return menu;
			}
		}

		FoundResource(std::string name, std::string path, Type^ type);
		FoundResource(FoundResource^ parent, FoundResource^ reference);
		FoundResource();

		virtual event PropertyChangedEventHandler^ PropertyChanged;

	private:
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew PropertyChangedEventArgs(name));
		}

		void OnRemove(Object^ sender, System::Windows::RoutedEventArgs^ e) {

		}
		void OnDelete(Object^ sender, System::Windows::RoutedEventArgs^ e) {

		}
		void OnChangeMesh(Object^ sender, System::Windows::RoutedEventArgs^ e) {

		}
	};
}