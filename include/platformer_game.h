#pragma once

#include "engine/game.h"
#include "game_constants.h"
#include "platformer_game/level1_scene.h"

using namespace GameConstants;

class PlatformerGame : public Game {
public:
	PlatformerGame() : Game(SCREEN_WIDTH, SCREEN_HEIGHT) {};
	int start() {
		Level1 *level1 = new Level1(getAssetLoader());
		level1->init();
		return runScene(level1);
	}
};
