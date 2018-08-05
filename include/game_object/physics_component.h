#pragma once

#include "math/geometry.h"
#include "input/input.h"
#include "engine/game_engine_constants.h"

using namespace GameEngineConstants;

class PhysicsComponent {

public:
	double x, y;
	double w, h;
	Vec2d velocity;
	Vec2d accel;
	PhysicsComponent() {};
	PhysicsComponent(double x, double y, double w, double h) :
		x(x), y(y), w(w), h(h) {
	};
	PhysicsComponent(Rect rect, Vec2d velocity) :
		x(rect.x), 
		y(rect.y), 
		w(rect.w), 
		h(rect.h), 
		velocity(velocity) {
	};
	PhysicsComponent(Rect rect, Vec2d velocity, Vec2d accel) :
		x(rect.x),
		y(rect.y),
		w(rect.w),
		h(rect.h),
		velocity(velocity),
		accel(accel) {
	};
	virtual void update() {
		double del = MS_PER_UPDATE;
		x = x + velocity.x * del + 0.5 * accel.x * del * del;
		y = y + velocity.y * del + 0.5 * accel.y * del * del;
		velocity.x += accel.x * del;
		velocity.y += accel.y * del;
	};
	Rect getRect() { return Rect(x, y, w, h); };
	~PhysicsComponent() {};
};
