#pragma once

#include "video/canvas.h"
#include "physics_component.h"
#include <SDL_image.h>

class GraphicsComponent {

public:
    virtual void draw ( Canvas *canvas ) {};
};


class SimpleGraphicsComponent : public GraphicsComponent {
    PhysicsComponent *physics;
    SDL_Rect boundingBox;
    SDL_Texture *texture;
public:
    void setPhysics ( PhysicsComponent *physics );
    void setTexture ( SDL_Texture *texture );
    void draw ( Canvas *canvas );
};
