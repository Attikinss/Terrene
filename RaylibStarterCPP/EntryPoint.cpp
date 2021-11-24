#include "raylib.h"
#include "Game.h"

int main()
{
	Game game;

	InitWindow(1600, 900, "Terrene");

	game.Init();

	while (!WindowShouldClose())
	{
		game.Update();
		game.Draw();
	}

	game.Shutdown();
	CloseWindow();
} 