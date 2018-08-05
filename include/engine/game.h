#pragma once

#include "sdl/sdl_system.h"
#include "sdl/asset_loader.h"
#include "input/input_poller.h"
#include "engine/game_loop.h"
#include "video/canvas.h"
#include "scene/scene.h"

class Game {
    SDLSystem *sdlSystem;
    InputPoller *inputPoller;
    GameLoop *gameLoop;
    AssetLoader *assetLoader;
    Canvas *canvas;

  public:
    Game(int width, int height);
    AssetLoader* getAssetLoader();
    int runScene(Scene *scene);
    virtual int start() { return 0; }
};
