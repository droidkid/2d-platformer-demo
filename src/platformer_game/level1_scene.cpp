#include "platformer_game/level1_scene.h"
#include "engine/game_engine_constants.h"
#include "platformer_game/player.h"

using namespace GameEngineConstants;

void Level1::init() {
	// Create All Game Objects
	assetLoader->loadPNGintoTexture("assets/PNG/Backgrounds/set1_background.png", &background1);
	assetLoader->loadPNGintoTexture("assets/PNG/Backgrounds/set1_tiles.png", &background2);
	assetLoader->loadPNGintoTexture("assets/PNG/Backgrounds/set1_hills.png", &background3);

	assetLoader->loadPNGintoTexture("assets/PNG/Other/fluidBrown.png", &block);

	player = new PlayerGameObject(assetLoader);
}

void Level1::draw(Canvas *canvas) {
	
	canvas->clearScreen();

	canvas->drawTexture(background1, { 0, 0, 600, 480 });
	canvas->drawTexture(background2, { 0, 0, 600, 480 });
	canvas->drawTexture(background3, { 0, 0, 600, 480 });

	for (int i = 0; i < 600; i = i + 64) {
		canvas->drawTexture(block, {i, 310, 64, 64});
	}
	for (int i = 0; i < 600; i = i + 64) {
		canvas->drawTexture(block, {i, 310 + 64, 64, 64});
	}
	for (int i = 0; i < 600; i = i + 64) {
		canvas->drawTexture(block, {i, 310 + 128, 64, 64});
	}

	player->draw(canvas);

	canvas->renderScreen();
}

void Level1::update(Input *input) {

	player->update(input);

}
