#pragma once

#include "game_object/game_object.h"
#include "game_object/physics_component.h"
#include "game_object/graphics_component.h"
#include "game_object/logic_component.h"
#include "engine/game_engine_constants.h"
#include "game_constants.h"
#include "sdl/asset_loader.h"

const int BLOCK_HEIGHT = 30;


class BlockPhysicsComponent : public PhysicsComponent {
public:
	BlockPhysicsComponent() {};
	BlockPhysicsComponent(int x, int y, int w) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = BLOCK_HEIGHT;
	}
};

class BlockLogicComponent : public LogicComponent {
public:
	BlockLogicComponent() {};
	void update(PhysicsComponent *physics, Input *input) {};
};

class BlockGraphicsComponent : public GraphicsComponent {
	SDL_Texture *boxTexture;
	PhysicsComponent *physics;
public:
	BlockGraphicsComponent(PhysicsComponent *physics, AssetLoader *assetLoader) {
		this->physics = physics;
		assetLoader->loadPNGintoTexture("assets/blockGreen.png", &boxTexture);

	}
	void draw(Canvas *canvas) {
		SDL_Rect boundingBox = {
			physics->x,
			physics->y,
			physics->w,
			physics->h,
		};
		canvas->drawTexture(boxTexture , boundingBox);
	}
};

class BlockGameObject : public GameObject {
public:
	BlockGameObject(AssetLoader *assetLoader, int x, int y, int w) {
		this->physics = new BlockPhysicsComponent(x, y, w);
		this->graphics = new BlockGraphicsComponent(physics, assetLoader);
		this->logic = new BlockLogicComponent();
		this->objectType = BLOCK_OBJECT_TYPE;
	}
};

