#pragma once

#include "scene/scene.h"
#include "sdl/asset_loader.h"
#include "platformer_game/player.h"

class Level1 : public Scene {
	AssetLoader *assetLoader;
	SDL_Texture *background1;
	SDL_Texture *background2;
	SDL_Texture *background3;

	SDL_Texture *walk1;
	SDL_Texture *walk2;
	SDL_Texture *walk3;
	SDL_Texture *walk4;
	SDL_Texture *walk5;

	SDL_Texture *block;

	PlayerGameObject *player;

	int timer = 300;
	int walk_state = 1;
	double x = 0;
public:
	Level1(AssetLoader *assetLoader) : assetLoader(assetLoader) {};
	void init();
	void draw(Canvas *canvas);
	void update(Input *input);
};