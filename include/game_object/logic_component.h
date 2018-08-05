#pragma once

#include "physics_component.h"
#include "input/input.h"

class LogicComponent {

public:
	virtual void update(PhysicsComponent *physics, Input *input) {};
};
