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

const int TOTAL_WALKING_ANIMATION_CYCLE_MS = 200;
const int WALKING_ANIM_FRAME_1 = 200;
const int WALKING_ANIM_FRAME_2 = 100;
const double JUMP_VEL = -0.35;
const double JUMP_ACCEL = 0.001;

enum PlayerState {
	IDLE_LOOK_RIGHT,
	IDLE_LOOK_LEFT,
	// Combine FRAME1
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
	void test();
};

class PlayerLogicComponent : public LogicComponent {
public:
	double walking_speed;
	int walk_anim_timer;
	int jump_anim_timer;
	PlayerState playerState;

	PlayerLogicComponent();
	void update(PhysicsComponent *physics, Input *input);
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
	PlayerGameObject(AssetLoader *assetLoader) {
		PlayerPhysicsComponent *physics = new PlayerPhysicsComponent();
		PlayerLogicComponent *logic = new PlayerLogicComponent();
		PlayerGraphicsComponent *graphics = new PlayerGraphicsComponent(logic, physics, assetLoader);

		this->physics = physics;
		this->graphics = graphics;
		this->logic = logic;
	};
};

