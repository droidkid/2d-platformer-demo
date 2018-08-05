#pragma once
namespace GameEngineConstants {
	const int UPDATES_PER_SECOND = 100; // GAME SPEED, game is updated this times a second
	const int MS_PER_UPDATE = 1000 / UPDATES_PER_SECOND;
	const int MAX_GAME_OBJECTS = 100;
	const int MAX_OBSERVERS = 30;
	const int MAX_FPS = 60;
	const int MS_PER_FRAME_UPDATE = 1000 / MAX_FPS;
}
