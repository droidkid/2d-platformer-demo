#pragma once

#include "game_object/game_object.h"
#include "game_object/physics_component.h"
#include "game_object/graphics_component.h"
#include "game_object/logic_component.h"
#include "engine/game_engine_constants.h"
#include "game_constants.h"
#include "sdl/asset_loader.h"

using namespace GameEngineConstants;
using namespace GameConstants;

class EnemyPhysicsComponent : public PhysicsComponent {

};

class EnemyLogicComponent : public LogicComponent {

};

class EnemyGraphicsComponent : public GraphicsComponent {

};