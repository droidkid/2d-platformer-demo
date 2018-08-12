#pragma once

#include "scene/scene.h"
#include "sdl/asset_loader.h"
#include "platformer_game/player.h"
#include "platformer_game/enemy.h"
#include "platformer_game/world_camera.h"
#include "engine/collision_manager.h"

class Level1 : public Scene {
	AssetLoader *assetLoader;
	SDL_Texture *background1;
	SDL_Texture *background2;
	SDL_Texture *background3;

	SDL_Texture *block;

	PlayerGameObject *player;
	EnemyGameObject *enemy;
	WorldCamera *camera;

	CollisionManager *collisionManager;

	int timer = 300;
	int walk_state = 1;
	double x = 0;
public:
	Level1(AssetLoader *assetLoader) : assetLoader(assetLoader) {
		collisionManager = new CollisionManager();
	};
	void init();
	void draw(Canvas *canvas);
	void update(Input *input);
};