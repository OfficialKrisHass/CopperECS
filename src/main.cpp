#include "CopperECS.h"

#include <iostream>

int cCounter = 0;

struct Shape : public Component {

	float color = 5.0f;
	const static bool multipleOnOneObject = true;

};

struct Light : public Component {

	float intensity = 1.5f;

};

int main() {

	Scene scene;

	Object o = scene.CreateObject("False 1");

	Shape* s1 = o.AddComponent<Shape>();
	Shape* s2 = o.AddComponent<Shape>();
	Shape* s3 = o.AddComponent<Shape>();
	s1->color++; //6
	s2->color = 8.79f; //8.79
	s3->color--; //4

	o.RemoveComponent<Shape>(2);
	o.RemoveComponent<Shape>(1);
	o.RemoveComponent<Shape>(0);

	for (Shape* shape : o.GetComponents<Shape>()) {

		std::cout << shape->color << std::endl;

	}

	std::cin.get();
	return 0;

}