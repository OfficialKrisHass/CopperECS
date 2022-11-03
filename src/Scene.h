#pragma once

#include "Registry.h"

class Scene {

	friend class Object;

public:
	Object* CreateObject(const char* name = "Object") { return registry.CreateObject(this, name); }
	void DestroyObject(Object* obj) { registry.DestroyObject(obj->id); }
	void DestroyObject(Object obj)  { registry.DestroyObject(obj.id); }

private:
	Registry registry;

};