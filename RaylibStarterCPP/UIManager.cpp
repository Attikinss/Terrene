#include "UIManager.h"
#include "raylib.h"
#include "Agent.h"
#include "GameManager.h"

using namespace std;

UIManager* UIManager::s_instance = nullptr;

UIManager::UIManager()
{
	m_debugViewActive = false;
}

UIManager::~UIManager()
{

}

void UIManager::Create()
{
	if (s_instance == nullptr)
		s_instance = new UIManager();
}

void UIManager::Destroy()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

void UIManager::Init()
{
	m_cursorIcons = TextureManager::GetInstance()->GetAllCursorSprites();
	m_uiElements = TextureManager::GetInstance()->GetAllUISprites();
}

void UIManager::Update()
{
	m_mousePosition = { (float)GetMouseX(), (float)GetMouseY() };
}

Vec2 UIManager::MousePosition()
{
	return m_mousePosition;
}

void UIManager::HighlightAgent(Agent* agent)
{
	Color selectionColor;
	if (agent->m_selected)
	{
		selectionColor = GOLD;
		DrawCircleGradient((int)agent->m_position.x + 5, (int)agent->m_position.y + 5, (float)TILE_SIZE, BLANK, selectionColor);
	}
	else if (agent->m_mouseOver)
	{
		if (!agent->m_selected)
		{
			selectionColor = WHITE;
			selectionColor.a = 200;
			DrawCircleGradient((int)agent->m_position.x + 5, (int)agent->m_position.y + 5, (float)TILE_SIZE, BLANK, selectionColor);
		}
	}
}

void UIManager::DisplayAgentInfo(Agent* agent)
{
	Vec2 windowPos = { agent->m_position.x + 10, agent->m_position.y + 10 };

	// Background
	Color uiTabColor = BLACK;
	uiTabColor.a = 200;
	DrawRectangle((int)windowPos.x, (int)windowPos.y, 184, 136, uiTabColor);

	// Border
	Rectangle rec = { windowPos.x, windowPos.y, 184, 136 };
	DrawRectangleLinesEx(rec, 5, DARKGRAY);

	// Text
	DrawText(agent->m_animal.GetName(), (int)windowPos.x + 15, (int)(int)windowPos.y + 10, 25, WHITE);
	DrawText(agent->m_currTaskText, (int)windowPos.x + 15, (int)windowPos.y + 35, 15, WHITE);
	DrawText(agent->m_animal.m_stats.c_str(), (int)windowPos.x + 35, (int)windowPos.y + 60, 11, WHITE);
	if (!agent->m_animal.m_alive)
		DrawText("*DEAD*", (int)windowPos.x + 103, (int)windowPos.y + 15, 17, RED);

	// Icons
	Color iconColor = WHITE;
	Texture iconUp = TextureManager::GetInstance()->GetUISprite("UpIcon");
	Texture iconDown = TextureManager::GetInstance()->GetUISprite("DownIcon");

	if (agent->m_drinking)
		DrawTexture(iconUp, (int)windowPos.x + 16, (int)windowPos.y + 78, iconColor);
	else
		DrawTexture(iconDown, (int)windowPos.x + 16, (int)windowPos.y + 78, iconColor);
	if (agent->m_eating)
		DrawTexture(iconUp, (int)windowPos.x + 16, (int)windowPos.y + 93, iconColor);
	else
		DrawTexture(iconDown, (int)windowPos.x + 16, (int)windowPos.y + 93, iconColor);
	if (agent->m_sleeping)
		DrawTexture(iconUp, (int)windowPos.x + 16, (int)windowPos.y + 108, iconColor);
	else
		DrawTexture(iconDown, (int)windowPos.x + 16, (int)windowPos.y + 108, iconColor);

	// Thirst icon
	if (!agent->IsThirsty())
		iconColor = GRAY;
	DrawTexture(TextureManager::GetInstance()->GetUISprite("ThirstyIcon"), (int)windowPos.x + 120, (int)windowPos.y + 70, iconColor);

	// Hunger icon
	if (!agent->IsHungry())
		iconColor = GRAY;
	DrawTexture(TextureManager::GetInstance()->GetUISprite("HungryIcon"), (int)windowPos.x + 120, (int)windowPos.y + 100, iconColor);

	// Energy icon
	if (!agent->IsTired())
		iconColor = GRAY;
	DrawTexture(TextureManager::GetInstance()->GetUISprite("TiredIcon"), (int)windowPos.x + 150, (int)windowPos.y + 70, iconColor);

	// Alert icon
	if (!agent->EnemyNear())
		iconColor = GRAY;
	DrawTexture(TextureManager::GetInstance()->GetUISprite("AlertIcon"), (int)windowPos.x + 150, (int)windowPos.y + 100, iconColor);
}

void UIManager::DrawCursor()
{
	switch (GameManager::GetInstance()->m_mouseState)
	{
		case MouseState::Attack:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "Attack")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		case MouseState::Delete:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "Delete")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		case MouseState::GoTo:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "GoTo")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		case MouseState::Select:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "Select")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		case MouseState::SpawnSheep:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "SpawnSheep")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		case MouseState::SpawnWolf:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "SpawnWolf")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		case MouseState::Invalid:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "Invalid")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;

		default:
			for (Sprite s : m_cursorIcons)
			{
				if (s.m_name == "Select")
					DrawTexture(s.m_texture, (int)m_mousePosition.x, (int)m_mousePosition.y, WHITE);
			}
			break;
	}
}