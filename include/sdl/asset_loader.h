#pragma once
#include "sdl/sdl_system.h"

class AssetLoader {
	SDL_Renderer *renderer;
public:
	void loadPNGintoTexture(char *fpath, SDL_Texture **texture);
	void loadTTFfont(char *fpath, int fontSize, TTF_Font **font);
	AssetLoader(SDLSystem *sdl);
};
