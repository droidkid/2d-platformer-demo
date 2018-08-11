#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "sdl/sdl_system.h"

class Canvas {
    SDL_Renderer *renderer;
public:
    Canvas ( SDLSystem *sdl );
    void clearScreen();
    void renderScreen();
    void drawText(char *text, int x, int y, TTF_Font *font, SDL_Color color);
    void drawTexture(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTextureHFlip(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTextureVFlip(SDL_Texture *texture, SDL_Rect *boundingBox);
    void drawTexture(SDL_Texture *texture, SDL_Rect boundingBox);
    void drawTextureHFlip(SDL_Texture *texture, SDL_Rect boundingBox);
    void drawTextureVFlip(SDL_Texture *texture, SDL_Rect boundingBox);
    ~Canvas() {};
};
