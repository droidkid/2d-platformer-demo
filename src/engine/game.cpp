#include "engine/game.h"

Game::Game(int width, int height) {
    sdlSystem = new SDLSystem(width, height);
    assetLoader = new AssetLoader(sdlSystem);
    inputPoller = new InputPoller();
    canvas = new Canvas(sdlSystem);
    gameLoop = new GameLoop(inputPoller, canvas);
}

AssetLoader* Game::getAssetLoader() {
  return assetLoader;
}

int Game::runScene(Scene *scene) {
  gameLoop->runLoop(scene);
  // TODO: make this return a value from gameLoop
  return 0;
}
