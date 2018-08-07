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

const double ENEMY_NORMAL_WALKING_SPEED = 1.0;
const int ENEMY_WALK_ANIM_CYCLE_TIME_MS = 300;
const int ENEMY_WALK_ANIM_FRAME_1_MS = 300;
const int ENEMY_WALK_ANIM_FRAME_2_MS = 150;
const int ENEMY_TURN_TIME_MS = 1000;

class EnemyPhysicsComponent : public PhysicsComponent {
public:
	EnemyPhysicsComponent() {
		x = 400;
		y = GROUND_LEVEL-21;
		w = 16;
		h = 21;
	}
};

class EnemyLogicComponent : public LogicComponent {
public:
	double walking_speed;
	int walk_anim_timer;
	int turn_timer;

	EnemyLogicComponent();
	void update(PhysicsComponent *physics, Input *input);

};

class EnemyGraphicsComponent : public GraphicsComponent {
	EnemyLogicComponent *logic;
	EnemyPhysicsComponent *physics;

	SDL_Texture *walkTexture1;
	SDL_Texture *walkTexture2;
public:
	EnemyGraphicsComponent(
		EnemyLogicComponent *logic,
		EnemyPhysicsComponent *physics,
		AssetLoader *assetLoader
	) : logic(logic), physics(physics) {
		assetLoader->loadPNGintoTexture("assets/enemyWalking_1.png", &walkTexture1);
		assetLoader->loadPNGintoTexture("assets/enemyWalking_2.png", &walkTexture2);
	}

	void draw(Canvas *canvas);
};

class EnemyGameObject : public GameObject {
public:
	EnemyGameObject(AssetLoader *assetLoader) {
		EnemyPhysicsComponent *physics = new EnemyPhysicsComponent();
		EnemyLogicComponent *logic = new EnemyLogicComponent();
		EnemyGraphicsComponent *graphics = new EnemyGraphicsComponent(logic, physics, assetLoader);

		this->physics = physics;
		this->graphics = graphics;
		this->logic = logic;
	}
};
