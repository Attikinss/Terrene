#pragma once
#include "raylib.h"
#include "GameManager.h"
#include "Agent.h"

class Game
{
public:
	GameManager* gameMgr = nullptr;

	Game() {}

	void Init();
	void Shutdown();
	void Update();
	void Draw();
};