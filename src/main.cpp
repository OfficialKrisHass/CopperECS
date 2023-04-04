#include "CopperECS.h"

#include <iostream>

int cCounter = 0;

#define CheckSuccess(x) if(x) {std::cout << "   Success!" << std::endl; } else {std::cout << "   Failure! This is really bad and mean and it makes me sad :c" << std::endl; }

class Transform : public Component {

public:
	Transform() {

		std::cout << "Created Transform!" << std::endl;

	}

	void Added() override {

		std::cout << "Added Transform to Entity: " << GetEntity()->name << " (" << GetEntity()->ID() << ")" << std::endl;

	}
	void Removed() override {

		std::cout << "Removed Transform from Entity: " << GetEntity()->name << " (" << GetEntity()->ID() << ")" << std::endl;

	}

	float x = 0.0f;

};
class Mesh : public Component {

public:
	void Added() override {

		std::cout << "Added a Mesh to Entity: " << GetEntity()->name << " (" << GetEntity()->ID() << ")" << std::endl;
		numOfMeshes++;

	}

	int numOfMeshes = 0;
	Transform* parent = nullptr;

};
class Light : public Component {

public:
	int r;

};

Scene scene;
Entity e;
Entity e1;
Entity third;

Transform* transform;
Transform* another;
Mesh* mesh;

void TestEntityCreation();
void TestComponentAdding();
void TestComponentEntityPointers();
void TestEntityRemoval();
void TestComponentRemoval();
void TestComponentView();
void TestEntityView();

int main() {

	for (Transform* t : ComponentView<Transform>(&scene)) {



	}
	for (Entity entity : EntityView(&scene)) {



	}
	
	TestEntityCreation();
	TestComponentAdding();
	TestComponentEntityPointers();
	TestEntityRemoval();
	TestComponentRemoval();
	TestComponentView();
	TestEntityView();

	scene.RemoveEntityFromID(1);
	scene.RemoveEntityFromID(4);
	scene.RemoveEntityFromID(5);
	scene.RemoveEntityFromID(7);

	for (Transform* t : ComponentView<Transform>(&scene)) {



	}
	for (Entity entity : EntityView(&scene)) {



	}

	std::cin.get();
	return 0;

}

void TestEntityCreation() {

	std::cout << "--------Entity Creation--------" << std::endl;

	e = scene.CreateEntity("Chris");
	e1 = scene.CreateEntity("Husky");
	std::cout << "Entity 0:       " << e->name << " (" << e->ID() << ")"; CheckSuccess(e->name == "Chris" && e->ID() == 0);
	std::cout << "Entity 1:       " << e1->name << " (" << e1->ID() << ")"; CheckSuccess(e1->name == "Husky" && e1->ID() == 1);

	Entity test = scene.GetEntityFromID(0);
	std::cout << "Entity From ID: " << test->name << " (" << test->ID() << ")"; CheckSuccess(test->name == "Chris" && test->ID() == 0);
	std::cout << std::endl;

}
void TestComponentAdding() {

	std::cout << "--------Component Adding--------" << std::endl;

	transform = e->AddComponent<Transform>();
	e1->AddComponent<Transform>();
	std::cout << "Transform:              " << transform->x; CheckSuccess(transform->x == 0.0f);
	std::cout << "Transform Got:          " << e->GetComponent<Transform>()->x; CheckSuccess(e->GetComponent<Transform>()->x == 0.0f);

	transform->x = 10.0f;
	std::cout << "Modified Transform:     " << transform->x; CheckSuccess(transform->x == 10.0f);
	std::cout << "Modified Transform Got: " << e->GetComponent<Transform>()->x; CheckSuccess(e->GetComponent<Transform>()->x == 10.0f);
	std::cout << std::endl;

	mesh = e->AddComponent<Mesh>();
	std::cout << "Mesh:              " << mesh->numOfMeshes; CheckSuccess(mesh->numOfMeshes == 1);
	std::cout << "Mesh Got:          " << e->GetComponent<Mesh>()->numOfMeshes; CheckSuccess(e->GetComponent<Mesh>()->numOfMeshes == 1);

	mesh->numOfMeshes++;
	std::cout << "Mesh:     " << mesh->numOfMeshes; CheckSuccess(mesh->numOfMeshes == 2);
	std::cout << "Mesh Got: " << e->GetComponent<Mesh>()->numOfMeshes; CheckSuccess(e->GetComponent<Mesh>()->numOfMeshes == 2);
	std::cout << std::endl;

}
void TestComponentEntityPointers() {

	std::cout << "--------Component Entity pointers-----------" << std::endl;
	std::cout << "Transform->entity: " << transform->GetEntity()->name << " (" << transform->GetEntity()->ID() << ")"; CheckSuccess(transform->GetEntity()->name == "Chris" && transform->GetEntity()->ID() == 0);
	std::cout << "Mesh->entity:      " << mesh->GetEntity()->name <<  "(" << mesh->GetEntity()->ID() << ")"; CheckSuccess(mesh->GetEntity()->name == "Chris" && mesh->GetEntity()->ID() == 0);

	third = scene.CreateEntity("Third uwu");

	std::cout << "Transform->entity: " << transform->GetEntity()->name << " (" << transform->GetEntity()->ID() << ")"; CheckSuccess(transform->GetEntity()->name == "Chris" && transform->GetEntity()->ID() == 0);
	std::cout << "Mesh->entity:      " << mesh->GetEntity()->name << " (" << mesh->GetEntity()->ID() << ")"; CheckSuccess(mesh->GetEntity()->name == "Chris" && mesh->GetEntity()->ID() == 0);
	std::cout << std::endl;

	another = third->AddComponent<Transform>();
	std::cout << "Another Transform: " << another->x; CheckSuccess(another->x == 0.0f);
	std::cout << "Default Transform: " << transform->x; CheckSuccess(transform->x == 10.0f);
	std::cout << "Mesh:              " << mesh->numOfMeshes; CheckSuccess(mesh->numOfMeshes == 2);
	std::cout << std::endl;

	std::cout << "Another Transform->entity: " << another->GetEntity()->name << " (" << another->GetEntity()->ID() << ")"; CheckSuccess(another->GetEntity()->name == "Third uwu" && another->GetEntity()->ID() == 2);
	std::cout << "Transform->entity:         " << transform->GetEntity()->name << " (" << transform->GetEntity()->ID() << ")"; CheckSuccess(transform->GetEntity()->name == "Chris" && transform->GetEntity()->ID() == 0);
	std::cout << "Transform->entity Got:     " << e->GetComponent<Transform>()->GetEntity()->name << " (" << e->GetComponent<Transform>()->GetEntity()->ID() << ")"; CheckSuccess(e->GetComponent<Transform>()->GetEntity()->name == "Chris" && e->GetComponent<Transform>()->GetEntity()->ID() == 0);
	std::cout << "Mesh->entity:      " << mesh->GetEntity()->name << "(" << mesh->GetEntity()->ID() << ")"; CheckSuccess(mesh->GetEntity()->name == "Chris" && mesh->GetEntity()->ID() == 0);
	std::cout << std::endl;

}
void TestEntityRemoval() {

	std::cout << "--------Entity Removal--------" << std::endl;
	scene.RemoveEntity(third);

	std::cout << "Entity Third:     "; if (*third == nullptr) std::cout << "nullptr"; CheckSuccess(*third == nullptr);
	std::cout << "Entity Third Got: "; if (scene.GetEntityFromID(2) == nullptr) std::cout << "nullptr"; CheckSuccess(scene.GetEntityFromID(2) == nullptr);
	std::cout << std::endl;

	std::cout << "Another Transform:     " << another->x; CheckSuccess(another->x == 0.0f);

	Entity anotherOne = scene.CreateEntity("Another one bites the dust");
	std::cout << "New Entity After deletion: " << anotherOne->name << " (" << anotherOne->ID() << ")"; CheckSuccess(anotherOne->name == "Another one bites the dust" && anotherOne->ID() == 2);
	std::cout << "Entity Third Got:          " << scene.GetEntityFromID(2)->name << " (" << scene.GetEntityFromID(2)->ID() << ")"; CheckSuccess(scene.GetEntityFromID(2)->name == "Another one bites the dust" && scene.GetEntityFromID(2)->ID() == 2);
	std::cout << std::endl;

	Transform* t = anotherOne->AddComponent<Transform>();
	std::cout << "New Transform:     " << t->x; CheckSuccess(t->x == 0.0f);
	std::cout << "Old Transform:     " << another->x; CheckSuccess(another->x == 0.0f);

	t->x = 15.0f;
	std::cout << "New Transform:     " << t->x; CheckSuccess(t->x == 15.0f);
	std::cout << "Old Transform:     " << another->x; CheckSuccess(another->x == 15.0f);
	std::cout << std::endl;

}
void TestComponentRemoval() {

	std::cout << "--------Component Removal--------" << std::endl;
	e1->RemoveComponent<Transform>();

	std::cout << "e1 Has Transform: " << e1->HasComponent<Transform>(); CheckSuccess(e1->HasComponent<Transform>() == false);
	Transform* e1Trans = e1->GetComponent<Transform>();
	std::cout << "e1 Transform Got: ";
	if (e1Trans) std::cout << e1Trans->x;
	else std::cout << "NULL"; CheckSuccess(!e1Trans);
	std::cout << std::endl;

	Mesh* mesh1 = e1->AddComponent<Mesh>();
	std::cout << "Mesh:              " << mesh1->numOfMeshes; CheckSuccess(mesh1->numOfMeshes == 1);
	std::cout << "Mesh Got:          " << e1->GetComponent<Mesh>()->numOfMeshes; CheckSuccess(e1->GetComponent<Mesh>()->numOfMeshes == 1);
	std::cout << "Mesh->entity:      " << mesh1->GetEntity()->name << "(" << mesh1->GetEntity()->ID() << ")"; CheckSuccess(mesh1->GetEntity()->name == "Husky" && mesh1->GetEntity()->ID() == 1);
	std::cout << std::endl;

}
void TestComponentView() {

	std::cout << "--------Component View--------" << std::endl;

	Entity e2 = scene.CreateEntity("Correct one");
	Entity e3 = scene.CreateEntity("Wrong one");
	Entity e4 = scene.CreateEntity("Wrong one");
	Entity e5 = scene.CreateEntity("Correct one");
	Entity e6 = scene.CreateEntity("Wrong one");

	//Expected output
	//0 - Has
	//1 - Doesn't - Exists
	//2 - Has
	//3 - Has
	//4 - Doesn't -Exists
	//5 - Doesn't - Removed
	//6 - Has
	//7 - Doesn't - Exists

	e2->AddComponent<Transform>();
	e5->AddComponent<Transform>();
	scene.RemoveEntity(e4);
	std::cout << std::endl;

	for (Transform* transform : ComponentView<Transform>(&scene)) {

		std::cout << "transform->entity: " << transform->GetEntity()->name << " (" << transform->GetEntity()->ID() << ")" << std::endl;

	}

	std::cout << std::endl;

}
void TestEntityView() {

	std::cout << "--------Entity View--------" << std::endl;

	//Expected output
	//0 - Incorrect
	//1 - Correct
	//2 - Incorrect
	//3 - Incorrect
	//4 - Correct
	//5 - Correct
	//6 - Incorrect
	//7 - Correct
	//8 - Incorrect

	scene.CreateEntityFromID(5);
	scene.CreateEntity("Eight");

	scene.RemoveEntityFromID(0);
	scene.RemoveEntityFromID(2);
	scene.RemoveEntityFromID(3);
	scene.RemoveEntityFromID(6);
	scene.RemoveEntityFromID(8);

	for (Entity entity : EntityView(&scene)) {

		std::cout << entity->name << " (" << entity->ID() << ")" << std::endl;

	}

}