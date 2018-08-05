#include "platformer_game/player.h"


PlayerLogicComponent::PlayerLogicComponent() {
	playerState = IDLE_LOOK_RIGHT;
	walking_speed = 3.0;
}

void PlayerLogicComponent::update(PhysicsComponent *physics, Input *input) {
	PlayerState oldPlayerState = playerState;
	switch (oldPlayerState) {
	case IDLE_LOOK_RIGHT:
	case IDLE_LOOK_LEFT:
		if (input->leftKeyDown) {
			playerState = WALKING_LEFT_FRAME_1;
			physics->x -= walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else if (input->rightKeyDown) {
			playerState = WALKING_RIGHT_FRAME_1;
			physics->x += walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}

		// Do Jump calc after movement calc
		if (input->spacePressed) {
			if (oldPlayerState == IDLE_LOOK_LEFT) {
				playerState = JUMP_LEFT_FRAME;
				physics->velocity.y = JUMP_VEL;
				physics->accel.y = JUMP_ACCEL;
			}
			if (oldPlayerState == IDLE_LOOK_RIGHT) {
				playerState = JUMP_RIGHT_FRAME;
				physics->velocity.y = JUMP_VEL;
				physics->accel.y = JUMP_ACCEL;
			}
		}
		break;
	case WALKING_RIGHT_FRAME_1:
	case WALKING_RIGHT_FRAME_2:
		if (input->rightKeyDown) {
			if (walk_anim_timer < 0) {
				walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
			}
			if (walk_anim_timer < WALKING_ANIM_FRAME_1) {
				playerState = WALKING_RIGHT_FRAME_1;
			}
			if (walk_anim_timer < WALKING_ANIM_FRAME_2) {
				playerState = WALKING_RIGHT_FRAME_2;
			}
			walk_anim_timer -= MS_PER_UPDATE;
			physics->x += walking_speed;
		}
		else if (input->leftKeyDown) {
			playerState = WALKING_LEFT_FRAME_1;
			physics->x -= walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else {
			playerState = IDLE_LOOK_RIGHT;
		}

		if (input->spacePressed) {
			playerState = JUMP_RIGHT_FRAME;
			physics->velocity.y = JUMP_VEL;
			physics->accel.y = JUMP_ACCEL;
		}
		break;
	case WALKING_LEFT_FRAME_1:
	case WALKING_LEFT_FRAME_2:
		if (input->rightKeyDown) {
			playerState = WALKING_RIGHT_FRAME_1;
			physics->x += walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else if (input->leftKeyDown) {
			if (walk_anim_timer < 0) {
				walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
			}
			if (walk_anim_timer < WALKING_ANIM_FRAME_1) {
				playerState = WALKING_LEFT_FRAME_1;
			}
			if (walk_anim_timer < WALKING_ANIM_FRAME_2) {
				playerState = WALKING_LEFT_FRAME_2;
			}
			walk_anim_timer -= MS_PER_UPDATE;
			physics->x -= walking_speed;
		}
		else {
			playerState = IDLE_LOOK_LEFT;
		}

		if (input->spacePressed) {
			playerState = JUMP_LEFT_FRAME;
			physics->velocity.y = JUMP_VEL;
			physics->accel.y = JUMP_ACCEL;
		}
		break;
	case JUMP_LEFT_FRAME:
		if (input->leftKeyDown) {
			playerState = JUMP_LEFT_FRAME;
			physics->x -= walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else if (input->rightKeyDown) {
			playerState = JUMP_RIGHT_FRAME;
			physics->x += walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}

		if (!input->spacePressed) {
			if (physics->velocity.y < 0) {
				physics->velocity.y -= physics->velocity.y;
			}
		}
		if (physics->y > 255) {
			playerState = IDLE_LOOK_LEFT;
			physics->y = 255;
			physics->accel.y = 0;
			physics->velocity.y = 0;
		}
		break;
	case JUMP_RIGHT_FRAME:
		if (input->leftKeyDown) {
			playerState = JUMP_LEFT_FRAME;
			physics->x -= walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else if (input->rightKeyDown) {
			playerState = JUMP_RIGHT_FRAME;
			physics->x += walking_speed;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}

		if (!input->spacePressed) {
			if (physics->velocity.y < 0) {
				physics->velocity.y -= physics->velocity.y;
			}
		}
		if (physics->y > 255) {
			playerState = IDLE_LOOK_RIGHT;
			physics->y = 255;
			physics->accel.y = 0;
			physics->velocity.y = 0;
		}

		break;
	default:
		break;
	}

	if (physics->x < 0) {
		physics->x = 600 - physics->w;
	}
	if (physics->x > 600) {
		physics->x = 0;
	}

	physics->y += physics->velocity.y * MS_PER_UPDATE + 0.5 * physics->accel.y * MS_PER_UPDATE * MS_PER_UPDATE;
	physics->y += physics->accel.y * MS_PER_UPDATE;
}


void PlayerGraphicsComponent::draw(Canvas *canvas) {
	SDL_Rect boundingBox = { 
		physics->x , 
		physics->y, 
		physics->w, 
		physics->h 
	};
	switch (logic->playerState) {
	case WALKING_LEFT_FRAME_1:
		canvas->drawTextureHFlip(
			walkTexture1,
			boundingBox
		);
		break;
	case WALKING_RIGHT_FRAME_1:
		canvas->drawTexture(
			walkTexture1,
			boundingBox
		);
		break;
	case WALKING_LEFT_FRAME_2:
		canvas->drawTextureHFlip(
			walkTexture2,
			boundingBox
		);
		break;
	case WALKING_RIGHT_FRAME_2:
		canvas->drawTexture(
			walkTexture2,
			boundingBox
		);
		break;
	case IDLE_LOOK_LEFT:
		canvas->drawTextureHFlip(
			idleTexture,
			boundingBox
		);
		break;
	case IDLE_LOOK_RIGHT:
		canvas->drawTexture(
			idleTexture,
			boundingBox
		);
		break;
	case JUMP_RIGHT_FRAME:
		canvas->drawTexture(
			jumpTexture,
			boundingBox
		);
		break;
	case JUMP_LEFT_FRAME:
		canvas->drawTextureHFlip(
			jumpTexture,
			boundingBox
		);
		break;
	default:
		break;
	}
}