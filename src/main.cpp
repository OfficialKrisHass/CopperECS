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

	Object o0 = scene.CreateObject("False 1");
	Object o1 = scene.CreateObject("Invalid 1");
	Object o2 = scene.CreateObject("Right 1");
	Object o3 = scene.CreateObject("Right 2");
	Object o4 = scene.CreateObject("False 2");
	Object o5 = scene.CreateObject("Right 3");
	Object o6 = scene.CreateObject("False 3");

	scene.DestroyObject(o1);

	Shape* s1 = o0.AddComponent<Shape>();
	Shape* s2 = o0.AddComponent<Shape>();
	Shape* s3 = o0.AddComponent<Shape>();
	s1->color++;
	s2->color = 8.79f;
	s3->color--;
	o2.AddComponent<Shape>();
	o3.AddComponent<Shape>();
	o4.AddComponent<Shape>();
	//o5.AddComponent<Shape>();
	o6.AddComponent<Shape>();


	o2.RemoveComponent<Shape>();
	//o5.RemoveComponent<Shape>();

	for (Shape* shape : o5.GetComponents<Shape>()) {

		std::cout << shape->color << std::endl;

	}

	std::cin.get();
	return 0;

}