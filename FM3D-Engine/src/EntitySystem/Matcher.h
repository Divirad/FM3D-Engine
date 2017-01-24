#pragma once
#include <Engine.h>

namespace FM3D {
	namespace EntitySystem {

		class Matcher;
		using MatcherList = std::vector<Matcher>;
		class Entity;
		///Pointer auf ein FM3D::Entity Objekt
		/**
		* Es wird ein std::shared_ptr verwendet statt einem
		* normalen Pointer um zu verhindern, dass das Entity
		* von einem anderen Thread gelöscht wird, während es
		* noch verwendet wird.
		*/
		using EntityPtr = std::shared_ptr<Entity>;

		///Sucht passende Entities
		/**
		* Vergleicht die Komponenten eines Entities mit
		* den gespeicherten. Hierbei kann ausgewählt welche
		* Komponenten das Entity beinhalten muss, wleche es
		* nicht beinhalten darf und von wlechen es mindestens
		* eins haben muss.
		*/
		class ENGINE_DLL Matcher {
		public:
			using MatcherChangedEvent = Event<void(Matcher* sender)>;

			MatcherChangedEvent OnMatcherChangedEvent;
		private:
			///Alle benötigten Ids
			/**
			* Speichert alle Ids, welche das zu vergleichende
			* FM3D::Entity besitzen muss.
			*/
			ComponentIdList m_allOfIds;
			///Alle nicht erlaubten Ids
			/**
			* Speichert alle Ids, welche das zu vergleichende
			* FM3D::Entity nicht besitzen darf.
			*/
			ComponentIdList m_noneOfIds;
			///Alle optionalen Ids
			/**
			* Speichert alle Id-Listen, von denen das zu vergleichende
			* FM3D::Entity mindestens eins enthalten muss.
			*/
			std::vector<ComponentIdList> m_anyOfIds;

			size_t m_hash;
		public:
			Matcher();
			Matcher(const Matcher& other);
			Matcher& AllOf(ComponentIdList ids);
			//Matcher& AllOf(ComponentIdList&& ids);
			Matcher& NoneOf(ComponentIdList ids);
			//Matcher& NoneOf(ComponentIdList&& ids);
			Matcher& AnyOf(ComponentIdList ids);
			//Matcher& AnyOf(ComponentIdList&& ids);

			bool IsEmpty() const;
			bool Matches(const EntityPtr& entity);
			void ClearIds();

			const ComponentIdList& GetAllOfIndices() const;
			const ComponentIdList& GetNoneOfIndices() const;
			const std::vector<ComponentIdList>& GetAnyOfIndices() const;

			bool operator ==(const Matcher& right) const;
			size_t GetHash() const;
		private:
			void CalcHash();
		};
	}
}

	namespace std {
		template <>
		struct hash<FM3D::EntitySystem::Matcher> {
			std::size_t operator()(const FM3D::EntitySystem::Matcher& matcher) const {
				return matcher.GetHash();
			}
	};
}