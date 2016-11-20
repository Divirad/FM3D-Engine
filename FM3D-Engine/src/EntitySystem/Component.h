#pragma once

namespace ENGINE_NAME {

	struct Component {
	protected:
		Component() = default;
	};

	typedef unsigned int ComponentId;
	typedef std::vector<ComponentId> ComponentIdList;

	class ComponentIds
	{
	public:
		template<typename T>
		static const ComponentId Get()
		{
			static_assert((std::is_base_of<IComponent, T>::value && !std::is_same<IComponent, T>::value),
				"Class T must be derived from Component");

			static ComponentId id = mCounter++;
			return id;
		}

		static unsigned int Count()
		{
			return mCounter;
		}

	private:
		static unsigned int mCounter;
	};
}