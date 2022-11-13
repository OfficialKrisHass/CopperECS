#pragma once

#include "Scene.h"

#include <iostream>

struct SceneViewIterator {

public:
	SceneViewIterator(Registry* registry, std::bitset<maxComponents> cMask, bool all, int32_t index, int32_t endIndex)
		: registry(registry), componentMask(cMask), all(all), index(index), endIndex(endIndex) {}

	Object& operator*() const {

		return registry->GetObjectFromID(index);

	}

	bool operator!=(const SceneViewIterator& other) const {

		return index != other.index && ValidObject();

		return index != other.index && index != registry->GetNumOfObjects();

	}

	SceneViewIterator& operator++() {

		do {

			index++;

		} while (index < endIndex && !ValidObject());

		return *this;

	}

private:
	int32_t index;
	int32_t endIndex;
	Registry* registry;
	std::bitset<maxComponents> componentMask;
	bool all = false;

	bool ValidObject() const {

		return registry->GetObjectFromID(index) && (all || componentMask == (componentMask & registry->GetObjectFromID(index).GetComponentMask()));

	}

};

template<typename ... Components> class SceneView {

public:
	SceneView(Scene* scene) : registry(scene->GetRegistry()), endIndex(/*(registry->GetNumOfObjects() - 1) < 0 ? 0 : registry->GetNumOfObjects() - 1*/registry->GetNumOfObjects()) {

		if (sizeof...(Components) == 0) { all = true; } else {

			int componentIDs[] = { 0, GetCID<Components>()... };

			for (int i = 1; i < (sizeof...(Components) + 1); i++) {

				componentMask.set(componentIDs[i]);

			}

		}

		while (beginIndex < registry->GetNumOfObjects() - 1 && (!registry->GetObjectFromID(beginIndex) || componentMask != (componentMask & registry->GetObjectFromID(beginIndex).GetComponentMask()))) { beginIndex++; }
		//while (endIndex >= 0 && endIndex > beginIndex && (!registry->GetObjectFromID(endIndex) || componentMask != (componentMask & registry->GetObjectFromID(endIndex).GetComponentMask()))) { endIndex--; }

	}

	const SceneViewIterator begin() const { return SceneViewIterator(registry, componentMask, all, beginIndex, endIndex); }
	const SceneViewIterator end() const { return SceneViewIterator(registry, componentMask, all, endIndex, endIndex); }

private:
	Registry* registry = nullptr;
	std::bitset<maxComponents> componentMask;

	int32_t beginIndex = 0;
	int32_t endIndex;

	bool all = false;

};