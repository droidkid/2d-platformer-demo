#pragma once

#include "game_object/game_object.h"
#include "game_object/physics_component.h"
#include "game_object/graphics_component.h"
#include "game_object/logic_component.h"
#include "engine/game_engine_constants.h"
#include "game_constants.h"
#include "sdl/asset_loader.h"

using namespace GameEngineConstants;
using namespace GameConstants;

const int TOTAL_WALKING_ANIMATION_CYCLE_MS = 300;
const int WALKING_ANIM_FRAME_1 = 300;
const int WALKING_ANIM_FRAME_2 = 150;
const int PLAYER_SPRITE_WIDTH = 40;
const int PLAYER_SPRITE_HEIGHT = 55;
const double JUMP_VEL = -0.45;
const double JUMP_ACCEL = 0.001;
const double WALKING_ACCEL = 0.0004;
const double WALKING_DECEL = -0.004;
const double NORMAL_WALKING_SPEED = 0.20;
const double FAST_WALKING_SPEED = 0.40;

enum PlayerState {
	IDLE,
	WALKING,
	JUMPING
};

class PlayerPhysicsComponent : public PhysicsComponent {
public:
	PlayerPhysicsComponent() {
		x = 150;
		y = GROUND_LEVEL - PLAYER_SPRITE_HEIGHT;
		w = PLAYER_SPRITE_WIDTH;
		h = PLAYER_SPRITE_HEIGHT;
	}
};

class PlayerLogicComponent : public LogicComponent {
public:
	double max_walking_speed;
	double max_jumping_speed;
	int walk_anim_timer;
	int jump_anim_timer;
	int is_looking_right;
	int prev_x_position;
	int space_released_after_jump;
	PlayerState playerState;

	PlayerLogicComponent();
	void update(PhysicsComponent *physics, Input *input);
private:
	void updateHeroPos(PhysicsComponent *physics);
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
		AssetLoader *assetLoader) :
		logic(logic), physics(physics) {
		assetLoader->loadPNGintoTexture("assets/player_idle.png", &idleTexture);
		assetLoader->loadPNGintoTexture("assets/player_walk1.png", &walkTexture1);
		assetLoader->loadPNGintoTexture("assets/player_walk2.png", &walkTexture2);
		assetLoader->loadPNGintoTexture("assets/player_jump.png", &jumpTexture);
	}

	void draw(Canvas *canvas);
};


class PlayerGameObject : public GameObject {
public:
	PlayerLogicComponent *playerLogic;
	PlayerGameObject(AssetLoader *assetLoader) {
		PlayerPhysicsComponent *physics = new PlayerPhysicsComponent();
		playerLogic = new PlayerLogicComponent();
		PlayerGraphicsComponent *graphics = new PlayerGraphicsComponent(playerLogic, physics, assetLoader);

		this->physics = physics;
		this->graphics = graphics;
		this->logic = playerLogic;
		this->objectType = PLAYER_OBJECT_TYPE;
	};

	void onCollision(GameObject *otherGameObject) {
		switch (otherGameObject->getObjectType()) {
		case ENEMY_OBJECT_TYPE:
			handleEnemyCollision(otherGameObject);
			break;
		case BLOCK_OBJECT_TYPE:
			handleBlockCollision(otherGameObject);
		default:
			break;
		}
	}
private:
	void handleEnemyCollision(GameObject *enemyObject);
	void handleBlockCollision(GameObject *gameObject);
};

