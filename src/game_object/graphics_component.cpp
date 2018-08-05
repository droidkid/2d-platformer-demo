#include "game_object/graphics_component.h"
#include "game_object/physics_component.h"
#include <SDL.h>
#include <SDL_image.h>

// Holds texture and does drawing of sprite.

void SimpleGraphicsComponent::setPhysics ( PhysicsComponent *physics ) {
    this->physics = physics;
}

void SimpleGraphicsComponent::setTexture ( SDL_Texture *texture ) {
    this->texture = texture;
}

void SimpleGraphicsComponent::draw ( Canvas *canvas ) {
    double x = physics->x;
    double y = physics->y;
    double w = physics->w;
    double h = physics->h;

    boundingBox.x = ( int ) ( x );
    boundingBox.y = ( int ) ( y );
    boundingBox.w = ( int ) ( w );
    boundingBox.h = ( int ) ( h );


    canvas->drawTexture ( texture, &boundingBox );
}
