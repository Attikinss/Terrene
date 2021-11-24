#include "TextureManager.h"

TextureManager* TextureManager::s_instance = nullptr;

TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	for (SpriteWrapper sw : m_spriteWrappers)
	{
		UnloadTexture(sw.m_faceUp.m_texture);
		UnloadTexture(sw.m_faceDown.m_texture);
		UnloadTexture(sw.m_faceLeft.m_texture);
		UnloadTexture(sw.m_faceRight.m_texture);
	}

	for (Sprite s : m_uiSprites)
	{
		UnloadTexture(s.m_texture);
	}

	for (Sprite s : m_terrainSprites)
	{
		UnloadTexture(s.m_texture);
	}

	UnloadTexture(m_missingTexture.m_texture);
	UnloadTexture(m_missingSprites.m_faceUp.m_texture);
	UnloadTexture(m_missingSprites.m_faceDown.m_texture);
	UnloadTexture(m_missingSprites.m_faceLeft.m_texture);
	UnloadTexture(m_missingSprites.m_faceRight.m_texture);
	UnloadTexture(m_missingSprites.m_poseSleep.m_texture);
	UnloadTexture(m_missingSprites.m_poseDeath.m_texture);
}

void TextureManager::Init()
{
	// Load in all textures for the game

	// Terrain textures
	AddTerrainTextureFromFile("Grass", "Art/grass.png");
	AddTerrainTextureFromFile("Water", "Art/water.png");
	AddTerrainTextureFromFile("Sand", "Art/sand.png");
	AddTerrainTextureFromFile("PineTree", "Art/pinetree2.png");
	AddTerrainTextureFromFile("Fern", "Art/fern.png");
	
	// Cursor textures
	AddCursorTextureFromFile("SpawnSheep", "Art/cursor_sheep.png");
	AddCursorTextureFromFile("SpawnWolf", "Art/cursor_wolf.png");
	AddCursorTextureFromFile("Select", "Art/cursor_general.png");
	AddCursorTextureFromFile("Delete", "Art/cursor_delete.png");
	AddCursorTextureFromFile("Invalid", "Art/cursor_invalid.png");

	// UI element textures
	AddUITextureFromFile("ThirstyIcon", "Art/icon_thirsty.png");
	AddUITextureFromFile("HungryIcon", "Art/icon_hungry.png");
	AddUITextureFromFile("TiredIcon", "Art/icon_sleep.png");
	AddUITextureFromFile("AlertIcon", "Art/icon_alert.png");
	AddUITextureFromFile("UpIcon", "Art/icon_up.png");
	AddUITextureFromFile("DownIcon", "Art/icon_down.png");

	// Agent textures
	AddAgentSpritesFromFile("Wolf", "Art/wolfUp.png", "Art/wolfDown.png", "Art/wolfLeft.png", "Art/wolfRight.png", "Art/wolfSleep.png", "Art/wolfDead.png");
	AddAgentSpritesFromFile("Sheep", "Art/sheepUp.png", "Art/sheepDown.png", "Art/sheepLeft.png", "Art/sheepRight.png", "Art/sheepSleep.png", "Art/sheepDead.png");

	// "Missing" textures ** MESSY BUT WORKS ** 
	Image missingImg = LoadImage("Art/error_texture.png");
	Image missingAnimalImg = LoadImage("Art/error_animal.png");
	Texture missingTex = LoadTextureFromImage(missingImg);
	Texture missingAnimalTex = LoadTextureFromImage(missingAnimalImg);

	m_missingTexture = { "Missing", missingTex };
	m_missingSprites = { "Missing", Sprite{"Missing", missingAnimalTex}, Sprite{"Missing", missingAnimalTex}, Sprite{"Missing", missingAnimalTex}, Sprite{"Missing", missingAnimalTex}, Sprite{"Missing", missingAnimalTex}, Sprite{"Missing", missingAnimalTex} };

	UnloadImage(missingImg);
	UnloadImage(missingAnimalImg);
}

void TextureManager::AddAgentSpritesFromFile(const char* swName, const char* texUp, const char* textDown, const char* texLeft, const char* texRight, const char* texSleep, const char* texDeath)
{
	Image imageU = LoadImage(texUp);
	Image imageD = LoadImage(textDown);
	Image imageL = LoadImage(texLeft);
	Image imageR = LoadImage(texRight);
	Image imageSleep = LoadImage(texSleep);
	Image imageDeath = LoadImage(texDeath);
	
	// Create sprites and add it to sprite wrapper
	Sprite up = { "Up", LoadTextureFromImage(imageU) };
	Sprite down = { "Down", LoadTextureFromImage(imageD) };
	Sprite left = { "Left", LoadTextureFromImage(imageL) };
	Sprite right = { "Right", LoadTextureFromImage(imageR) };
	Sprite sleep = { "Sleep", LoadTextureFromImage(imageSleep) };
	Sprite dead = { "Dead", LoadTextureFromImage(imageDeath) };

	SpriteWrapper sw = { swName, up, down, left, right, sleep, dead };
	m_spriteWrappers.push_back(sw);

	UnloadImage(imageU);
	UnloadImage(imageD);
	UnloadImage(imageL);
	UnloadImage(imageR);
	UnloadImage(imageSleep);
	UnloadImage(imageDeath);
}

void TextureManager::AddTerrainTextureFromFile(const char* textureName, const char* filePath)
{
	Image image = LoadImage(filePath);

	Sprite s = { textureName, LoadTextureFromImage(image) };
	m_terrainSprites.push_back(s);

	UnloadImage(image);
}

void TextureManager::AddCursorTextureFromFile(const char* textureName, const char* filePath)
{
	Image image = LoadImage(filePath);

	Sprite s = { textureName, LoadTextureFromImage(image) };
	m_cursorSprites.push_back(s);

	UnloadImage(image);
}

void TextureManager::AddUITextureFromFile(const char* textureName, const char* filePath)
{
	Image image = LoadImage(filePath);

	Sprite s = { textureName, LoadTextureFromImage(image) };
	m_uiSprites.push_back(s);

	UnloadImage(image);
}

Texture TextureManager::GetTerrainSprite(const char* reqName)
{
	for (Sprite s : m_terrainSprites)
	{
		if (s.m_name == reqName)
			return s.m_texture;
	}

	return m_missingTexture.m_texture;
}

Texture TextureManager::GetUISprite(const char* reqName)
{
	for (Sprite s : m_uiSprites)
	{
		if (s.m_name == reqName)
			return s.m_texture;
	}

	return m_missingTexture.m_texture;
}

std::vector<Sprite> TextureManager::GetAllUISprites()
{
	return m_uiSprites;
}

std::vector<Sprite> TextureManager::GetAllCursorSprites()
{
	return m_cursorSprites;
}

SpriteWrapper TextureManager::GetSpriteWrapper(const char* reqName)
{
	for (SpriteWrapper sw : m_spriteWrappers)
	{
		if (sw.m_name == reqName)
			return sw;
	}

	return m_missingSprites;
}

void TextureManager::Create()
{
	if (s_instance == nullptr)
		s_instance = new TextureManager();
}

void TextureManager::Destroy()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
