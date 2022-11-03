#include "CopperECS.h"

#include <iostream>
#include <memory>

int cCounter = 0;

int main() {

	Scene scene;

	Object* o0 = scene.CreateObject("Square");
	Object* o1 = scene.CreateObject("Light");
	Object* o2 = scene.CreateObject("Cube");

	o0->transform->rotation = 90.0f;
	o1->transform->position = -1.0f;
	o2->transform->scale = 2.0f;
	
	scene.DestroyObject(*o1);
	std::cout << o1->transform->position;

	std::cout << "Hello, World!" << std::endl;
	std::cin.get();

	return 0;

}