#pragma once
#include <string>

namespace ArkanoidGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
	const std::string GAME_NAME = "Arkanoid Game";

	// Game settings constants
	const float PLATFORM_SIZE = 50.f;
	const float BALL_SIZE = 30.f;
	const unsigned int TILE_SIZE = 20;
	const float INITIAL_PLATFORM_SPEED = 500.f;
	const float INITIAL_BALL_SPEED = 300.f;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps
	const int POINTS_PER_TILE = 100;
	const int MAX_TILES = 20;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some SPP
}
