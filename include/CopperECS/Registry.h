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

	friend class Scene;

public:
	Object CreateObject(Scene* scene, std::string name) {

		if (!gaps.empty()) {

			int32_t id = gaps.front();

			objects[id].id = id;
			objects[id].scene = scene;
			objects[id].name = name;

			gaps.erase(gaps.begin());

			return objects[id];

		}

		int32_t id = (int32_t) objects.size();
		objects.push_back(Object());

		objects[id].id = id;
		objects[id].scene = scene;
		objects[id].name = name;
		//name.copy(objects[id].name.data(), name.size(), 0);

		return objects[id];

	}
	Object CreateObjectFromID(int32_t id, Scene* scene, std::string name) {

		if (id > (int32_t) objects.size() - 1) objects.resize(id + 1, Object());

		objects[id].id = id;
		objects[id].scene = scene;
		objects[id].name = name;

		return objects[id];

	}
	void DestroyObject(Object& obj) {

		gaps.push_back(obj.id);

		objects[obj.id] = Object();

	}

	template<typename T> T* AddComponent(Object& obj) {

		if (!obj) return nullptr;
		if (!objects[obj.id]) return nullptr;

		int cID = GetCID<T>();

		if (pools.size() <= cID) pools.resize(cID + 1, nullptr);
		if (pools[cID] == nullptr) pools[cID] = new ComponentPool(sizeof(T));

		T* component = new (pools[cID]->Get(obj.id)) T();
		objects[obj.id].componentMask.set(cID);
		obj.componentMask.set(cID);

		return component;

	}
	template<typename T> T* GetComponent(int32_t id) {

		if (!objects[id]) return nullptr;

		int cID = GetCID<T>();
		if (!objects[id].componentMask.test(cID)) return nullptr;

		T* component = static_cast<T*>(pools[cID]->Get(id));
		return component;

	}
	template<typename T> bool HasComponent(int32_t id) {

		if (!objects[id]) return false;

		int cID = GetCID<T>();
		
		return objects[id].componentMask.test(cID);

	}
	template<typename T> void RemoveComponent(Object& obj) {

		if (!obj) return;
		if (!objects[obj.id]) return;

		int cID = GetCID<T>();
		if (!objects[obj.id].componentMask.test(cID)) return;

		objects[obj.id].componentMask.reset(cID);
		obj.componentMask.reset(cID);

	}

	int GetNumOfObjects() { return (int) objects.size(); }
	Object GetObjectFromID(int32_t id) { return objects[id]; }
	std::string GetObjectName(Object obj) { return objects[obj.id].name; }

	void SetObjectName(std::string name, Object obj) { obj.name = name; objects[obj.id].name = name; }

private:
	std::vector<Object> objects;
	std::vector<uint32_t> gaps;
	std::vector<ComponentPool*> pools;

};