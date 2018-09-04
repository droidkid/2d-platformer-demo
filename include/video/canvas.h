#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "sdl/sdl_system.h"
#include "video/camera.h"

class Canvas {
    SDL_Renderer *renderer;
	Camera *camera;
public:
    Canvas ( SDLSystem *sdl );
    void clearScreen();
    void renderScreen();
	void setCamera(Camera *camera);
    void drawText(char *text, int x, int y, TTF_Font *font, SDL_Color color);
    void drawTexture(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTextureDebug(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTextureHFlip(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTextureVFlip(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTexture(SDL_Texture *texture, SDL_Rect boundingBox);
    void drawTextureHFlip(SDL_Texture *texture, SDL_Rect boundingBox);
    void drawTextureVFlip(SDL_Texture *texture, SDL_Rect boundingBox);
    ~Canvas() {};
};
