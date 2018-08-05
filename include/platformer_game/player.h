#pragma once

#include "game_object/game_object.h"
#include "game_object/physics_component.h"
#include "game_object/graphics_component.h"
#include "game_object/logic_component.h"
#include "engine/game_engine_constants.h"
#include "game_constants.h"

using namespace GameEngineConstants;
using namespace GameConstants;

const int TOTAL_WALKING_ANIMATION_CYCLE_MS = 200;
const int WALKING_ANIM_FRAME_1 = 200;
const int WALKING_ANIM_FRAME_2 = 100;
const double JUMP_VEL = -0.35;
const double JUMP_ACCEL = 0.001;

enum PlayerState {
	IDLE_LOOK_RIGHT,
	IDLE_LOOK_LEFT,
	//    Combine FRAME1
	WALKING_RIGHT_FRAME_1,
	WALKING_RIGHT_FRAME_2,
	WALKING_LEFT_FRAME_1,
	WALKING_LEFT_FRAME_2,
	JUMP_LEFT_FRAME,
	JUMP_RIGHT_FRAME
};

class PlayerPhysicsComponent : public PhysicsComponent {
public:
	PlayerPhysicsComponent() {
		x = 150;
		y = 255;
		w = 40;
		h = 55;
	}
};

class PlayerLogicComponent : public LogicComponent {
public:
	double walking_speed;
	int walk_anim_timer;
	int jump_anim_timer;
	PlayerState playerState;

	PlayerLogicComponent() {
		playerState = IDLE_LOOK_RIGHT;
		walking_speed = 3.0;
	}

	void update(PhysicsComponent *physics, Input *input) {

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

		/*
		if (oldPlayerState == WALKING_LEFT_FRAME_1 || oldPlayerState ==WALKING_LEFT_FRAME_2) {
			playerState = IDLE_LOOK_LEFT;
		}
		if (oldPlayerState == WALKING_RIGHT_FRAME_1 || oldPlayerState == WALKING_RIGHT_FRAME_2) {
			playerState = IDLE_LOOK_RIGHT;
		}

		// Reset the walk_anim_timer if no key has been pressed.
		if (!input->rightKeyDown && !input->leftKeyDown) {
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
			return;
		}

		if (walk_anim_timer < 0) {
			walk_anim_timer = TOTAL_WALKING_ANIMATION_CYCLE_MS;
		}

		if (walk_anim_timer < WALKING_ANIM_FRAME_1) {
			if (input->rightKeyDown) {
				playerState = WALKING_RIGHT_FRAME_1;
			}
			if (input->leftKeyDown) {
				playerState = WALKING_LEFT_FRAME_1;
			}
		}
		if (walk_anim_timer < WALKING_ANIM_FRAME_2) {
			if (input->rightKeyDown) {
				playerState = WALKING_RIGHT_FRAME_2;
			}
			if (input->leftKeyDown) {
				playerState = WALKING_LEFT_FRAME_2;
			}
		}

		if (input->rightKeyDown) {
			physics->x += walking_speed;
		}
		if (input->leftKeyDown) {
			physics->x -= walking_speed;
		}

		if (physics->x + physics->w > SCREEN_WIDTH) {
			physics->x = 1;
		}

		if (physics->x < 0) {
			physics->x = SCREEN_WIDTH - physics->w;
		}

		walk_anim_timer -= MS_PER_UPDATE;
		*/
	}
};

class PlayerGraphicsComponent : public GraphicsComponent {
	PlayerLogicComponent *logic;
	PlayerPhysicsComponent *physics;
	SDL_Rect boundingBox;

	SDL_Texture *idleTexture;
	SDL_Texture *walkTexture1;
	SDL_Texture *walkTexture2;
	SDL_Texture *jumpTexture;
public:
	PlayerGraphicsComponent(
		PlayerLogicComponent *logic,
		PlayerPhysicsComponent *physics,
		AssetLoader *assetLoader) : logic(logic), physics(physics) {
		assetLoader->loadPNGintoTexture("assets/adventurer_idle.png", &idleTexture);
		assetLoader->loadPNGintoTexture("assets/adventurer_walk1.png", &walkTexture1);
		assetLoader->loadPNGintoTexture("assets/adventurer_walk2.png", &walkTexture2);
		assetLoader->loadPNGintoTexture("assets/adventurer_jump.png", &jumpTexture);
	}

	void draw(Canvas *canvas) {
		SDL_Rect boundingBox = { physics->x , physics->y, physics->w, physics->h };
		cout << logic->playerState << endl;
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
};


class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(AssetLoader *assetLoader) {
		PlayerPhysicsComponent *physics = new PlayerPhysicsComponent();
		PlayerLogicComponent *logic = new PlayerLogicComponent();
		PlayerGraphicsComponent *graphics = new PlayerGraphicsComponent(logic, physics, assetLoader);

		this->physics = physics;
		this->graphics = graphics;
		this->logic = logic;
	};
};

