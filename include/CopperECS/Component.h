#pragma once

#include "Entity.h"

class Component {

	friend class Registry;

public:
	virtual void Added() {}
	virtual void Removed() {}

	InternalEntity* GetEntity() const { return entity; }

	operator bool() const { return valid; }

private:
	Entity entity = nullptr;

protected:
	bool valid = false;

};