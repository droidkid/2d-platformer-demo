#include "engine/collision_manager.h"
#include "math/geometry.h"

void CollisionManager::addGameObject(GameObject *gameObject) {
	gameObjects.push_back(gameObject);
}

void CollisionManager::removeGameObject(GameObject *gameObject) {
	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObject == gameObjects[i]) {
			gameObjects.erase(gameObjects.begin() + i);
			break;
		}
	}
}

void CollisionManager::handleCollisions() {
	for (int i = 0; i < gameObjects.size(); i++) {
		for (int j = i + 1; j < gameObjects.size(); j++) {
			if (i == j || gameObjects[i] == gameObjects[j]) {
				continue;
			}

			if (isColliding(gameObjects[i], gameObjects[j])) {
				gameObjects[i]->onCollision(gameObjects[j]);
				gameObjects[j]->onCollision(gameObjects[i]);
			}
		}
	}
}

bool CollisionManager::isColliding(GameObject *object1, GameObject *object2) {
	Rect r1 = object1->getPhysics()->getRect();
	Rect r2 = object2->getPhysics()->getRect();

	return isRectIntersect(r1, r2);
}