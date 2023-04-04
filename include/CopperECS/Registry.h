#pragma once

#include <vector>

#include "Entity.h"

extern int cCounter;

class Registry {

	friend class Scene;

public:
	struct ComponentPool {

		ComponentPool() = default;
		ComponentPool(size_t size) : cSize(size), data(new char[size * maxComponents]) {}
		~ComponentPool() {

			delete[] data;

		}

		void* Add(uint32_t index) { validComponents.set(index); count++; return Get(index); }
		void* Get(uint32_t index) { return data + index * cSize; }
		void Remove(uint32_t index) { validComponents.reset(index); count--; }

		bool Valid(uint32_t index) { return validComponents.test(index); }
		uint32_t Count() { return count; }

	private:
		char* data = nullptr;
		std::bitset<maxComponents> validComponents;

		size_t cSize;
		uint32_t count = 0;

	};

public:
	InternalEntity* CreateEntity(Scene* scene, const std::string& name) {

		uint32_t id;
		if (gaps.empty()) {

			entities.push_back(InternalEntity());
			id = (uint32_t) entities.size() - 1;

		} else {

			id = gaps.back();
			gaps.pop_back();

		}

		entities[id].id = id;
		entities[id].name = name;
		entities[id].scene = scene;

		return &entities[id];

	}
	InternalEntity* CreateEntityFromID(uint32_t eID, Scene* scene, const std::string& name, bool returnIfExists) {

		if (eID > entities.size() - 1) entities.resize(eID + 1, InternalEntity());
		if (returnIfExists && entities[eID]) return &entities[eID];

		entities[eID].id = eID;
		entities[eID].name = name;
		entities[eID].scene = scene;

		for (int i = 0; i < gaps.size(); i++) {

			uint32_t gap = gaps[i];
			if (gap != eID) continue;

			gaps.erase(gaps.begin() + i);
			break;

		}

		return &entities[eID];

	}
	InternalEntity* GetEntityFromID(uint32_t eID) {
		
		if (eID == invalidID || eID > entities.size() - 1 || !entities[eID]) return nullptr;
		return &entities[eID];

	}
	void RemoveEntity(uint32_t eID) {

		entities[eID].Invalidate();
		gaps.push_back(eID);

		for (ComponentPool* pool : pools) {

			if (!pool->Valid(eID)) continue;
			pool->Remove(eID);

		}

	}

	template<typename T> T* AddComponent(uint32_t eID) {

		if (eID == invalidID) return nullptr;
		if (!entities[eID]) return nullptr;

		int cID = GetCID<T>();

		if (pools.size() < cID + 1) pools.resize(cID + 1, nullptr);
		if (!pools[cID]) pools[cID] = new ComponentPool(sizeof(T));

		T* component = new (pools[cID]->Add(eID)) T();
		component->entity = &entities[eID];
		component->valid = true;
		component->Added();

		entities[eID].cMask.set(cID);

		return component;

	}
	template<typename T> T* GetComponent(uint32_t eID) {

		if (eID == invalidID) return nullptr;
		if (!entities[eID]) return nullptr;

		int cID = GetCID<T>();
		if (!entities[eID].cMask.test(cID)) return nullptr;

		T* component = static_cast<T*>(pools[cID]->Get(eID));
		return component;

	}
	template<typename T> bool HasComponent(uint32_t eID) {

		if (eID == invalidID) return false;
		if (!entities[eID]) return false;

		int cID = GetCID<T>();
		return entities[eID].cMask.test(cID);

	}
	template<typename T> void RemoveComponent(uint32_t eID) {

		if (eID == invalidID) return;
		if (!entities[eID]) return;

		int cID = GetCID<T>();
		if (!entities[eID].cMask.test(cID)) return;

		pools[cID]->Remove(eID);
		entities[eID].cMask.reset(cID);

		T* component = static_cast<T*>(pools[cID]->Get(eID));
		component->Removed();
		component->valid = false;


	}

	template<typename T> static int GetCID() {

		static int cID = cCounter++;
		return cID;

	}

	void Cleanup() {

		for (ComponentPool* pool : pools) {

			delete pool;

		}

		entities.clear();
		gaps.clear();
		pools.clear();

	}

	ComponentPool* GetComponentPool(int cID) {

		if (pools.size() < cID + 1) return nullptr;

		return pools[cID];

	}

private:
	std::vector<InternalEntity> entities;
	std::vector<ComponentPool*> pools;
	std::vector<uint32_t> gaps;

};