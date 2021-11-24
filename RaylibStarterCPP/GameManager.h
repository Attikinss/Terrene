#pragma once
#include <iostream>
#include "raylib.h"
#include "TextureManager.h"
#include "AIManager.h"
#include "UIManager.h"
#include "Grid.h"

class Grid;

enum class MouseState
{
	Select,
	SpawnSheep,
	SpawnWolf,
	GoTo,
	Delete,
	Attack,
	Invalid
};

class GameManager
{
public:
	// Current state for mouse interaction
	MouseState m_mouseState = MouseState::Select;
	bool m_overrideMouseState = true;

	// Other managers
	TextureManager* textureMgr = nullptr;
	AIManager* aiMgr = nullptr;
	UIManager* uiMgr = nullptr;

	// Grid for agent A* pathfinding
	Grid* m_map = nullptr;

	static void Create();
	static void Destroy();
	static GameManager* GetInstance() { return s_instance; }

	std::vector<Node*> GetWaterNodes() { return m_waterNodes; }
	std::vector<Node*> GetFoodNodes() { return m_foodNodes; }

	void Init();
	void Update();
	Vec2 MousePosition();
	float DeltaTime() { return m_deltaTime; }
	bool DebugActive() { return m_debugViewActive; }
	void SetDebugStatus(bool status) { m_debugViewActive = status; }

private:
	static GameManager* s_instance;

	float m_deltaTime = 0;
	bool m_debugViewActive = false;
	Vec2 m_nodeSelected;
	Vec2 m_mousePosition;

	std::vector<Node*> m_waterNodes;
	std::vector<Node*> m_foodNodes;

	GameManager();
	~GameManager();
};