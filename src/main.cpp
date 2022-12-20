#include "CopperECS.h"

#include <iostream>

int cCounter = 0;

struct Shape : public Component {

	float color = 5.0f;
	const static bool multipleOnOneObject = false;

};

struct Light : public Component {

	float intensity = 1.5f;

};

struct Vector {

	Vector() : x(0.0f), y(0.0f) {}

	float x, y;

};

int main() {

	Vector x;

	x.x = 1.0f;
	x.y = 5.0f;

	Vector* y = &x;
	*y = Vector();

	Scene scene;

	Object o0 = scene.CreateObject("False 1");
	Object o1 = scene.CreateObject("Invalid 1");
	Object o2 = scene.CreateObject("Right 1");
	Object o3 = scene.CreateObject("Right 2");
	Object o4 = scene.CreateObject("False 2");
	Object o5 = scene.CreateObject("Right 3");
	Object o6 = scene.CreateObject("False 3");

	scene.DestroyObject(o1);

	o0.AddComponent<Shape>();
	o2.AddComponent<Shape>();
	o3.AddComponent<Shape>();
	o4.AddComponent<Shape>();
	o5.AddComponent<Shape>();
	o6.AddComponent<Shape>();

	o2.RemoveComponent<Shape>();
	o5.RemoveComponent<Shape>();

	for (Component* c : ComponentView<Shape>(&scene)) {

		std::cout << c->object->name << " ID: " << c->object->id << std::endl;

	}

	std::cin.get();
	return 0;

}