#pragma once

#include <vector>
#include <bitset>

#include "Object.h"

extern int cCounter;

template<typename T> int GetCID() {

	static int cID = cCounter++;
	return cID;

}

struct ComponentPool {

public:
	ComponentPool(size_t size) : size(size), data(new char[maxComponents * size]) {}
	~ComponentPool() { delete data; }

	void* Get(uint32_t index) { return data + index * size;  }

private:
	size_t size;
	char* data = nullptr;

};

class Registry {

public:
	Object* CreateObject(Scene* scene, const char* name) {

		if (!gaps.empty()) {

			Object obj;
			obj.id = gaps.front();
			obj.scene = scene;
			obj.name = name;
			obj.componentMask = &componentMasks[obj.id];
			obj.transform = AddComponent<Transform>(obj.id);

			gaps.erase(gaps.begin());
			objects[obj.id] = obj;

			return &objects[obj.id];

		}

		Object obj;
		obj.id = objects.size();
		obj.scene = scene;
		obj.name = name;

		componentMasks.push_back(std::bitset<maxComponents>());
		obj.componentMask = &componentMasks.back();
		objects.push_back(obj);

		objects[obj.id].transform = AddComponent<Transform>(obj.id);

		return &objects[obj.id];

	}
	void DestroyObject(int32_t id) {

		objects[id].id++;
		/*objects[id].scene = nullptr;
		objects[id].componentMask = nullptr;
		objects[id].name = nullptr;
		objects[id].transform = nullptr;*/

		componentMasks[id] = std::bitset<maxComponents>();

		gaps.push_back(id);

	}

	template<typename T> T* AddComponent(int32_t id) {

		if (!objects[id]) return nullptr;

		int cID = GetCID<T>();

		if (pools.size() <= cID) pools.resize(cID + 1, nullptr);
		if (pools[cID] == nullptr) pools[cID] = new ComponentPool(sizeof(T));

		T* component = new (pools[cID]->Get(id)) T();
		componentMasks[id].set(cID);

		return component;

	}
	template<typename T> T* GetComponent(int32_t id) {

		if (!objects[id]) return nullptr;

		int cID = GetCID<T>();
		if (!componentMasks[id].test(cID)) return nullptr;

		T* component = static_cast<T*>(pools[cID]->Get(id));
		return component;

	}
	template<typename T> void RemoveComponent(int32_t id) {

		if (!objects[id]) return;

		int cID = GetCID<T>();
		if (!componentMasks[id].test(cID)) return;

		componentMasks[id].reset(cID);

	}
	template<typename T> bool HasComponent(int32_t id) {

		if (!objects[id]) return false;

		int cID = GetCID<T>();
		
		return componentMasks[id].test(cID);

	}

private:
	std::vector<Object> objects;
	std::vector<uint32_t> gaps;

	std::vector<std::bitset<maxComponents>> componentMasks;
	std::vector<ComponentPool*> pools;

};