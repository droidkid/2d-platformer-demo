#include "platformer_game/player.h"
#include "platformer_game/enemy.h"

#include <iostream>
using namespace std;

PlayerLogicComponent::PlayerLogicComponent() {
	playerState = IDLE;
	max_walking_speed = NORMAL_WALKING_SPEED;
	max_jumping_speed = -JUMP_VEL;
	is_looking_right = 1;
	prev_x_position = 0;
}

void PlayerLogicComponent::update(PhysicsComponent *physics, Input *input) {
	PlayerState oldPlayerState = playerState;


	if (input->leftKeyDown && input->rightKeyDown) {
		input->leftKeyDown = 0;
		input->rightKeyDown = 0;
	}

	switch (oldPlayerState) {
	case IDLE:
		if (input->leftKeyDown) {
			playerState = WALKING;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		else if (input->rightKeyDown) {
			playerState = WALKING;
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}

		// Do Jump calc after movement calc

		physics->velocity.x = 0;
		physics->accel.x = 0;
		physics->accel.y = 0.0035;

		if (!input->spacePressed && !space_released_after_jump) {
			space_released_after_jump = 1;
		}

		if (input->spacePressed && space_released_after_jump) {
			playerState = JUMPING;
			space_released_after_jump = 0;
			physics->velocity.y = JUMP_VEL;
			physics->accel.y = JUMP_ACCEL;
		}
		updateHeroPos(physics);
		break;
	case WALKING:

		if (input->shiftPressed) {
			max_walking_speed = FAST_WALKING_SPEED;
		}
		else {
			max_walking_speed = NORMAL_WALKING_SPEED;
		}

		if (walk_anim_timer < 0) {
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}
		walk_anim_timer -= MS_PER_UPDATE;

		if (input->rightKeyDown) {
			physics->accel.x = WALKING_ACCEL;
		}
		else if (input->leftKeyDown) {
			physics->accel.x = -WALKING_ACCEL;
		}

		if (!input->spacePressed && !space_released_after_jump) {
			space_released_after_jump = 1;
		}
		physics->accel.y = 0.0035;

		if (input->spacePressed && space_released_after_jump) {
			playerState = JUMPING;
			space_released_after_jump = 0;
			physics->velocity.y = JUMP_VEL;
			physics->accel.y = JUMP_ACCEL;
		}

		if (!input->leftKeyDown &&
			!input->rightKeyDown &&
			!input->spacePressed
			) {
			playerState = IDLE;
		}
		updateHeroPos(physics);
		break;
	case JUMPING:
		if (input->rightKeyDown) {
			physics->accel.x = WALKING_ACCEL;
		}
		else if (input->leftKeyDown) {
			physics->accel.x = -WALKING_ACCEL;
		}
		else {
			physics->accel.x = 0;
		}

		if (!input->spacePressed && !space_released_after_jump) {
			space_released_after_jump = 1;
			physics->accel.y = 0.0035;
		}

		// If Player releases space early, makes the player make a
		// smaller jump.

		updateHeroPos(physics);
		break;
	default:
		break;
	}


	if (physics->velocity.x > 0) {
		is_looking_right = 1;
	}
	else if (physics->velocity.x < 0) {
		is_looking_right = 0;
	}

	if (physics->x < 0) {
		physics->x = 0;
	}
	if (physics->x + physics->w > WORLD_WIDTH) {
		physics->x = WORLD_WIDTH - physics->w;
	}

	prev_x_position = physics->x;

	if (physics->y + physics->h > GROUND_LEVEL) {
		physics->y = GROUND_LEVEL - physics->h;
		physics->accel.y = 0;
		physics->velocity.y = 0;
		if (input->rightKeyDown || input->leftKeyDown) {
			playerState = WALKING;
		}
		else {
			playerState = IDLE;
		}
	}


}


void PlayerGraphicsComponent::draw(Canvas *canvas) {
	SDL_Rect boundingBox = {
		physics->x ,
		physics->y,
		physics->w,
		physics->h
	};

	SDL_Texture **walkTexture = &walkTexture1;
	canvas->drawTextureDebug(*walkTexture, &boundingBox);

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

void PlayerGameObject::handleEnemyCollision(GameObject *enemyObject) {
	EnemyGameObject *enemy = (EnemyGameObject *)enemyObject;

	if (physics->velocity.y > 0 &&
		enemy->enemyLogicComponent->enemyState == ENEMY_WALKING) {

		physics->velocity.y = JUMP_VEL;
		physics->accel.y = JUMP_ACCEL;
	}
}

void PlayerGameObject::handleBlockCollision(GameObject *block) {
	if (physics->x + physics->w >= block->getPhysics()->x 
		&& physics->x + physics->w < block->getPhysics()->x + 3) {
		cout << "HERE1" << endl;
		physics->x = block->getPhysics()->x - physics->w;
		return;
	}
	else if (physics->x <= block->getPhysics()->x + block->getPhysics()->w
		&& physics->x > block->getPhysics()->x + block->getPhysics()->w - 3) {

		cout << "HERE2" << endl;
		physics->x = block->getPhysics()->x + block->getPhysics()->w;
		return;
	}

	if (physics->velocity.y > 0 && physics->y < block->getPhysics()->y ) {
		physics->y = block->getPhysics()->y - physics->h;
		if (playerLogic->playerState == JUMPING) {
			playerLogic->playerState = IDLE;
			if (physics->accel.x != 0) {
				playerLogic->playerState = WALKING;
			}
			physics->accel.y = 0;
			physics->velocity.y = 0;
		}
		cout << "HERE3" << endl;
	}

	else if (physics->velocity.y < 0.1 && physics->y > block->getPhysics()->y ) {
		physics->y = block->getPhysics()->y + block->getPhysics()->h;
			physics->accel.y = 0.001;
		cout << "HERE4" << endl;
	}

}

void PlayerLogicComponent::updateHeroPos(PhysicsComponent *physics) {

	physics->y += physics->velocity.y * MS_PER_UPDATE +
		0.5 * physics->accel.y * MS_PER_UPDATE * MS_PER_UPDATE;
	physics->velocity.y += physics->accel.y * MS_PER_UPDATE;

	physics->velocity.x += physics->accel.x * MS_PER_UPDATE;

	if (physics->velocity.x > max_walking_speed) {
		physics->velocity.x = max_walking_speed;
	}
	if (physics->velocity.x < -max_walking_speed) {
		physics->velocity.x = -max_walking_speed;
	}
	if (physics->velocity.y > max_jumping_speed) {
		physics->velocity.y = max_jumping_speed;
	}
	if (physics->velocity.y < -max_jumping_speed) {
		physics->velocity.y = -max_jumping_speed;
	}

	physics->x += physics->velocity.x * MS_PER_UPDATE +
		0.5 * physics->accel.x * MS_PER_UPDATE * MS_PER_UPDATE;

}

