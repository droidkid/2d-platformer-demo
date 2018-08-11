#pragma once

#include "game_object/physics_component.h"
#include "game_object/graphics_component.h"
#include "game_object/logic_component.h"

class GameObject {
protected:
	int objectType;
	PhysicsComponent *physics;
	GraphicsComponent *graphics;
	LogicComponent *logic;

public:
	GameObject() {
		objectType = -1;
		physics = NULL;
		graphics = NULL;
		logic = NULL;
	}
	GameObject(
		int objectType,
		PhysicsComponent *physics,
		GraphicsComponent *graphics,
		LogicComponent *logic) :
		objectType(objectType),
		physics(physics),
		graphics(graphics),
		logic(logic) {
	}

	int getObjectType() {
		return objectType;
	}

	void update(Input *input) {
		logic->update(physics, input);
		physics->update();
	}

	void draw(Canvas *canvas) {
		graphics->draw(canvas);
	}

	// Probably make this another Component.
	virtual void onCollision(GameObject *otherGameObject) {}

	PhysicsComponent* getPhysics() {
		return physics;
	}
};
