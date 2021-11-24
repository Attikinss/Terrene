#include "Game.h"
#include <sstream>	//String stream, used for the FPS counter

void Game::Init()
{
	GameManager::Create();
	gameMgr = GameManager::GetInstance();
	gameMgr->Init();

	HideCursor();
	SetTargetFPS(144);
}	

void Game::Shutdown()
{
	GameManager::Destroy();
}

void Game::Update()
{
	gameMgr->Update();
}

void Game::Draw()
{
	std::stringstream fpsCounter;
	fpsCounter << "FPS: " << GetFPS();

	BeginDrawing();
	ClearBackground(BLACK);

	// Draw terrain
	gameMgr->m_map->DrawTerrain();

	// Draw debug information
	if (gameMgr->DebugActive())
	{
		gameMgr->m_map->DrawDebug();
		gameMgr->aiMgr->DrawDebug();
		DrawText(fpsCounter.str().c_str(), 10, 10, 20, RED);
	}

	// Draw agents
	gameMgr->aiMgr->Draw();
	
	// Draw trees and bushes
	gameMgr->m_map->DrawFoliage();


	for (Agent* sheep : gameMgr->aiMgr->GetSheep())
	{
		if (sheep->m_selected)
			gameMgr->uiMgr->DisplayAgentInfo(sheep);
	}
	for (Agent* wolf : gameMgr->aiMgr->GetWolves())
	{
		if (wolf->m_selected)
			gameMgr->uiMgr->DisplayAgentInfo(wolf);
	}

	// Draw custom cursor
	gameMgr->uiMgr->DrawCursor();

	EndDrawing();
}