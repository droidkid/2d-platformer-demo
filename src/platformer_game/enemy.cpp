#include "platformer_game/enemy.h"

#include <iostream>
using namespace std;

EnemyLogicComponent::EnemyLogicComponent() {
	walking_speed = ENEMY_NORMAL_WALKING_SPEED;
	walk_anim_timer = ENEMY_WALK_ANIM_CYCLE_TIME_MS;
	turn_timer = ENEMY_TURN_TIME_MS;
}

void EnemyLogicComponent::update(PhysicsComponent *physics, Input *input) {
	walk_anim_timer -= MS_PER_UPDATE;
	turn_timer -= MS_PER_UPDATE;

	if (turn_timer < 0) {
		walking_speed = -walking_speed;
		turn_timer = ENEMY_TURN_TIME_MS;
	}

	if (walk_anim_timer < 0) {
		walk_anim_timer = ENEMY_WALK_ANIM_CYCLE_TIME_MS;
	}

	physics->x += walking_speed;
}

void EnemyGraphicsComponent::draw(Canvas *canvas) {
	SDL_Rect boundingBox = {
		physics->x ,
		physics->y,
		physics->w,
		physics->h
	};

	SDL_Texture **walkTexture = &walkTexture1;

	if (logic->walk_anim_timer < ENEMY_WALK_ANIM_FRAME_1_MS) {
		walkTexture = &walkTexture1;
	}
	if (logic->walk_anim_timer < ENEMY_WALK_ANIM_FRAME_2_MS) {
		walkTexture = &walkTexture2;
	}

	if (logic->walking_speed >= 0) {
		canvas->drawTexture(*walkTexture, boundingBox);
	}
	else {
		canvas->drawTextureHFlip(*walkTexture, boundingBox);
	}
}