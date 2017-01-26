#include "FoundResource.h"
#include "ExternResource.h"
#include "../pch.h"

namespace DesignerLib {

	FoundResource::FoundResource(std::string name, std::string path, ResourceType type, ExternResource^ master) {
		this->Name = ConvertString(name);
		this->Path = ConvertString(path);
		this->ResType = type;
		this->Content = gcnew ObservableCollection<FoundResource^>();
		this->IsReference = false;
		this->Master = master;

		this->Master->Resources->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &FoundResource::OnResourcesChanged);
	}

	FoundResource::FoundResource(System::String^ name, System::String^ path, ResourceType type, ExternResource^ master) {
		this->Name = name;
		this->Path = path;
		this->ResType = type;
		this->Content = gcnew ObservableCollection<FoundResource^>();
		this->IsReference = false;
		this->Master = master;

		this->Master->Resources->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &FoundResource::OnResourcesChanged);
	}

	FoundResource::FoundResource(FoundResource^ parent, FoundResource^ reference, ExternResource^ master) {
		this->Name = reference->Name;
		this->Path = "";
		this->ResType = reference->ResType;
		this->Content = nullptr;
		this->IsReference = true;
		this->Master = master;

		this->Master->Resources->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &FoundResource::OnResourcesChanged);
	}


	FoundResource::FoundResource() {
		this->Name = "Null-Name";
		this->Path = "Null-Path";
		this->ResType = ResourceType::Unknown;
		this->Content = gcnew ObservableCollection<FoundResource^>();
		this->IsReference = false;

		this->Master->Resources->CollectionChanged += gcnew System::Collections::Specialized::NotifyCollectionChangedEventHandler(this, &FoundResource::OnResourcesChanged);
	}

	ContextMenu^ FoundResource::CMenu::get() {
		auto menu = gcnew ContextMenu();

		if (ResType == ResourceType::MeshPart) {
			auto changeMesh = gcnew MenuItem();
			changeMesh->Header = "Change Mesh";
			changeMesh->Click += gcnew System::Windows::RoutedEventHandler(this, &FoundResource::OnChangeMesh);
			menu->Items->Add(changeMesh);
			int count = 0;
			for each(auto res in Master->Resources) {
				if (res->ResType == ResourceType::Mesh) count++;
			}
			if (count < 2) changeMesh->IsEnabled = false;
		}
		if (IsReference) {
			auto remove = gcnew MenuItem();
			remove->Header = "Remove";
			remove->Click += gcnew System::Windows::RoutedEventHandler(this, &FoundResource::OnRemove);
			menu->Items->Add(remove);
		}
		else {
			auto delet = gcnew MenuItem();
			delet->Header = "Delete";
			delet->Click += gcnew System::Windows::RoutedEventHandler(this, &FoundResource::OnDelete);
			menu->Items->Add(delet);
		}
		return menu;
	}

	void FoundResource::OnRemove(Object^ sender, System::Windows::RoutedEventArgs^ e) {
		this->Master->Master->OnRemove(this);
	}
	void FoundResource::OnDelete(Object^ sender, System::Windows::RoutedEventArgs^ e) {
		this->Master->Master->OnDelete(this);
	}
	void FoundResource::OnChangeMesh(Object^ sender, System::Windows::RoutedEventArgs^ e) {
		this->Master->Master->OnChangeMesh(this);
	}
}