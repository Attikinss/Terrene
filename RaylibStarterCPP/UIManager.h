#pragma once
#include "CustomMath.h"
#include "TextureManager.h"
#include <vector>

class Agent;

class UIManager
{
public:
	static void Create();
	static void Destroy();
	static UIManager* GetInstance() { return s_instance; }
	
	void Init();
	void Update();
	Vec2 MousePosition();
	void HighlightAgent(Agent* agent);
	void DisplayAgentInfo(Agent* agent);
	void DrawCursor();
	bool DebugActive() { return m_debugViewActive; }
	void SetDebugStatus(bool status) { m_debugViewActive = status; }

private:
	static UIManager* s_instance;
	bool m_debugViewActive = false;
	Vec2 m_mousePosition;

	// UI Elements
	std::vector<Sprite> m_cursorIcons;
	std::vector<Sprite> m_uiElements;

	UIManager();
	~UIManager();
};