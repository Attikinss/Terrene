#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "Sprite.h"

class TextureManager
{
public:
	void AddTerrainTextureFromFile(const char* textureName, const char* filePath);
	void AddCursorTextureFromFile(const char* textureName, const char* filePath);
	void AddUITextureFromFile(const char* textureName, const char* filePath);
	void AddAgentSpritesFromFile(const char* swName, const char* texUp, const char* textDown, const char* texLeft, const char* texRight, const char* texSleep, const char* texDeath);
	Texture GetTerrainSprite(const char* name);
	Texture GetUISprite(const char* name);
	std::vector<Sprite> GetAllUISprites();
	std::vector<Sprite> GetAllCursorSprites();
	SpriteWrapper GetSpriteWrapper(const char* reqName);

	void Init();
	static void Create();
	static void Destroy();
	static TextureManager* GetInstance() { return s_instance; }

private:
	TextureManager();
	~TextureManager();
	static TextureManager* s_instance;

	std::vector<SpriteWrapper> m_spriteWrappers;
	std::vector<Sprite> m_terrainSprites;
	std::vector<Sprite> m_cursorSprites;
	std::vector<Sprite> m_uiSprites;
	Sprite m_missingTexture;
	SpriteWrapper m_missingSprites;
};