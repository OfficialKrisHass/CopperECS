#pragma once

class Object;
class Registry;

struct Component {

	friend class Registry;

public:
	Object* object;
	uint32_t indexOnObject;

	bool Valid() const { return valid; }

private:
	const static bool multipleOnOneObject = true;
	
	bool valid;

};