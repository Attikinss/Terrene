#include "GameManager.h"
#include "Agent.h"
#include <sstream>	//String stream, used for the FPS counter

using namespace std;

GameManager* GameManager::s_instance = nullptr;

GameManager::GameManager()
{
	m_map = nullptr;
	m_debugViewActive = false;

	// Initialise managers
	if (textureMgr == nullptr)
	{
		TextureManager::Create();
		textureMgr = TextureManager::GetInstance();
	}
	if (aiMgr == nullptr)
	{
		AIManager::Create();
		aiMgr = AIManager::GetInstance();
	}
	if (uiMgr == nullptr)
	{
		UIManager::Create();
		uiMgr = UIManager::GetInstance();
	}
}

GameManager::~GameManager()
{
	m_waterNodes.clear();
	m_foodNodes.clear();

	delete m_map;
	textureMgr->Destroy();
	aiMgr->Destroy();
	uiMgr->Destroy();
}

void GameManager::Create()
{
	if (s_instance == nullptr)
		s_instance = new GameManager();
}

void GameManager::Destroy()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

void GameManager::Init()
{
	// Set init values for texture and ui managers
	textureMgr->Init();
	uiMgr->Init();

	// Create grid
	m_map = new Grid(GetScreenWidth() / TILE_SIZE, GetScreenHeight() / TILE_SIZE);

	for (int y = 0; y < m_map->gridSizeY; y++)
	{
		for (int x = 0; x < m_map->gridSizeX; x++)
		{
			if (m_map->nodes[x][y].m_type == NodeType::Water)
				m_waterNodes.push_back(&m_map->nodes[x][y]);

			else if (m_map->nodes[x][y].m_type == NodeType::Bush)
				m_foodNodes.push_back(&m_map->nodes[x][y]);
		}
	}
}

void GameManager::Update()
{
	m_mousePosition = { (float)GetMouseX(), (float)GetMouseY() };
	m_deltaTime = GetFrameTime();

	m_nodeSelected = { m_mousePosition.x / TILE_SIZE, m_mousePosition.y / TILE_SIZE };
	int x = (int)m_nodeSelected.x;
	int y = (int)m_nodeSelected.y;

	// If no agents, reset mouse icon
	if (aiMgr->NoAgents() && m_overrideMouseState)
	{
		m_overrideMouseState = true;
		m_mouseState = MouseState::Select;
	}

	// Select certain mouse icon
	if ((m_mouseState == MouseState::SpawnSheep && IsKeyPressed(KEY_ONE)) || (m_mouseState == MouseState::SpawnWolf) && IsKeyPressed(KEY_TWO))
	{
		m_overrideMouseState = true;
		m_mouseState = MouseState::Select;
	}
	else if (IsKeyPressed(KEY_ONE))
	{
		m_overrideMouseState = false;
		m_mouseState = MouseState::SpawnSheep;
	}
	else if (IsKeyPressed(KEY_TWO))
	{
		m_overrideMouseState = false;
		m_mouseState = MouseState::SpawnWolf;
	}

	// Display debug info
	if (IsKeyPressed(KEY_H))
		SetDebugStatus(!DebugActive()); /* **this inadvertently tanks performance - allows grid lines to be drawn ** */

	// Spawn agents
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		switch (m_mouseState)
		{
			case MouseState::SpawnSheep:
			{
				// Set up genes
				Genes genes(DietClass::Herbivore, (float)TILE_SIZE * 5.0f, 200.0f, 80.0f, 100.0f, 150.0f, 200.0f);
				// Create sheep
				Agent* newSheep = new Agent(&m_map->nodes[x][y], AnimalSelection::Sheep, genes);

				// Add sheep to game manager
				aiMgr->AddSheep(newSheep);
				break;
			}
			case MouseState::SpawnWolf:
			{
				// Set up genes
				Genes genes(DietClass::Carnivore, (float)TILE_SIZE * 10.0f, 250.0f, 120.0f, 150.0f, 150.0f, 350.0f);
				// Create wolf
				Agent* newWolf = new Agent(&m_map->nodes[x][y], AnimalSelection::Wolf, genes);

				// Add sheep to game manager
				aiMgr->AddWolf(newWolf);
				break;
			}
			default:
				break;
		}
	}

	// Update ui and ai
	uiMgr->Update();
	aiMgr->Update();
}

Vec2 GameManager::MousePosition()
{
	return m_mousePosition;
}
