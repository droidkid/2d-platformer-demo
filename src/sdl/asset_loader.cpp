#include "sdl/asset_loader.h"
#include "engine/game_engine_constants.h"

// Class to keep initialize and retrieve all resources (Textures, Fonts, Audio etc).

AssetLoader::AssetLoader(SDLSystem *sdl) {
	renderer = sdl->getRenderer();
}

void AssetLoader::loadPNGintoTexture(char *fpath, SDL_Texture **texture) {
	SDL_Surface *surface = IMG_Load(fpath);
	*texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void AssetLoader::loadTTFfont(char *fpath, int font_size, TTF_Font **font) {
	*font = TTF_OpenFont(fpath, font_size);
	if (*font == NULL) {
		SDL_Log("Failed to load text font: %s\n", TTF_GetError());
		throw "Failed to load text";
	}
}
