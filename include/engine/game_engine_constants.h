#pragma once
namespace GameEngineConstants {
	// GAME SPEED, game is updated this times a second
	const int UPDATES_PER_SECOND = 100;
	const int MS_PER_UPDATE = 1000 / UPDATES_PER_SECOND;
	const int MAX_GAME_OBJECTS = 100; // TODO(chesetti): Remove this.
	const int MAX_OBSERVERS = 30;
}
