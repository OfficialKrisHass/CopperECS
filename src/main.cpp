#include "CopperECS.h"

int cCounter = 0;

struct Shape : public Component {

	float color = 5.0f;

};

struct Light : public Component {

	float intensity = 1.5f;

};

int main() {

	Scene scene;

	Object o1 = scene.CreateObject("False 1");
	Object o2 = scene.CreateObject("Invalid 1");
	Object o3 = scene.CreateObject("Right 1");
	Object o4 = scene.CreateObject("Right 2");
	Object o5 = scene.CreateObject("False 2");
	Object o6 = scene.CreateObject("Right 3");
	Object o7 = scene.CreateObject("False 3");

	scene.DestroyObject(o2);

	o3.AddComponent<Shape>();
	o4.AddComponent<Shape>();
	o6.AddComponent<Shape>();

	for (Object& obj : SceneView<Shape>(&scene)) {

		std::cout << "Test" << std::endl;

	}

	return 0;

}