#pragma once

#include "game_object/game_object.h"

#include <vector>
using namespace std;

class CollisionManager {
public:
	vector<GameObject *> gameObjects;
	void addGameObject(GameObject *gameObject);
	void removeGameObject(GameObject *gameObject);
	void handleCollisions();
private:
	bool isColliding(GameObject *object1, GameObject *object2);
};