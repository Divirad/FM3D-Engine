#pragma once

namespace DesignerLib {

	public ref class ResourceRef : System::ComponentModel::INotifyPropertyChanged {
	protected:
		System::String^ _Name;
		System::String^ _Path;
		unsigned int _ID;
		System::WeakReference^ m_target;
	public:
		property System::String^ Name {
			System::String^ get() {
				return _Name;
			}
		}
		property unsigned int ID {
			unsigned int get() {
				return _ID;
			}
		}
		property bool IsLoaded {
			bool get() {
				return m_target ? m_target->IsAlive : false;
			}
		}
		property System::String^ Path {
			System::String^ get() {
				return _Path;
			}
		}

		virtual event System::ComponentModel::PropertyChangedEventHandler^ PropertyChanged;
	protected:
		ResourceRef() {
		};
		void OnPropertyChanged(System::String^ name) {
			this->PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(name));
		}
	};
}