#include "platformer_game/player.h"

#include <iostream>
using namespace std;

PlayerLogicComponent::PlayerLogicComponent() {
	playerState = IDLE;
	walking_speed = 1.5;
	is_looking_right = 1;
	prev_x_position = 0;
}

void PlayerLogicComponent::update(PhysicsComponent *physics, Input *input) {
	PlayerState oldPlayerState = playerState;
	switch (oldPlayerState) {
	case IDLE:
		if (input->leftKeyDown) {
			playerState = WALKING;
			physics->x -= walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else if (input->rightKeyDown) {
			playerState = WALKING;
			physics->x += walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}

		// Do Jump calc after movement calc
		if (input->spacePressed) {
			playerState = JUMPING;
			physics->velocity.y = JUMP_VEL;
			physics->accel.y = JUMP_ACCEL;
		}
		break;
	case WALKING:
		if (walk_anim_timer < 0) {
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		walk_anim_timer -= MS_PER_UPDATE;

		if (input->rightKeyDown) {
			physics->x += walking_speed;
		}
		if (input->leftKeyDown) {
			physics->x -= walking_speed;
		}

		if (input->spacePressed) {
			playerState = JUMPING;
			physics->velocity.y = JUMP_VEL;
			physics->accel.y = JUMP_ACCEL;
		}

		if (!input->leftKeyDown &&
			!input->rightKeyDown &&
			!input->spacePressed
			) {
			playerState = IDLE;
		}
		break;
	case JUMPING:
		if (input->leftKeyDown) {
			physics->x -= walking_speed;
		}
		else if (input->rightKeyDown) {
			physics->x += walking_speed;
		}

		if (!input->spacePressed) {
			if (physics->velocity.y < 0) {
				physics->velocity.y -= physics->velocity.y;
			}
		}

		if (physics->y > 255) {
			playerState = IDLE;
			physics->y = 255;
			physics->accel.y = 0;
			physics->velocity.y = 0;
		}
		break;
	default:
		break;
	}

	if (physics->x > prev_x_position) {
		is_looking_right = 1;
	}
	else if (physics->x < prev_x_position) {
		is_looking_right = 0;
	}

	if (physics->x < 0) {
		physics->x = 600 - physics->w;
		is_looking_right = 0;
	}
	if (physics->x > 600) {
		physics->x = 0;
		is_looking_right = 1;
	}
	prev_x_position = physics->x;

	physics->y += physics->velocity.y * MS_PER_UPDATE +
		0.5 * physics->accel.y * MS_PER_UPDATE * MS_PER_UPDATE;
	physics->y += physics->accel.y * MS_PER_UPDATE;

}


void PlayerGraphicsComponent::draw(Canvas *canvas) {
	SDL_Rect boundingBox = {
		physics->x ,
		physics->y,
		physics->w,
		physics->h
	};

	SDL_Texture **walkTexture = &walkTexture1;

	switch (logic->playerState) {
	case WALKING:
		if (logic->walk_anim_timer <= WALKING_ANIM_FRAME_1) {
			walkTexture = &walkTexture1;
		}
		if (logic->walk_anim_timer <= WALKING_ANIM_FRAME_2) {
			walkTexture = &walkTexture2;
		}
		if (logic->is_looking_right) {
			canvas->drawTexture(
				*walkTexture,
				boundingBox
			);
		}
		else {
			canvas->drawTextureHFlip(
				*walkTexture,
				boundingBox
			);
		}
		break;
	case IDLE:
		if (logic->is_looking_right) {
			canvas->drawTexture(
				idleTexture,
				boundingBox
			);
		}
		else {
			canvas->drawTextureHFlip(
				idleTexture,
				boundingBox
			);
		}
		break;
	case JUMPING:
		if (logic->is_looking_right) {
			canvas->drawTexture(
				jumpTexture,
				boundingBox
			);
		}
		else {
			canvas->drawTextureHFlip(
				jumpTexture,
				boundingBox
			);
		}
		break;
	default:
		break;
	}
}