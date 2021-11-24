#pragma once
#include "raylib.h"

struct Sprite
{
	const char* m_name;
	Texture m_texture;
};

struct SpriteWrapper
{
	const char* m_name;
	Sprite m_faceUp;
	Sprite m_faceDown;
	Sprite m_faceLeft;
	Sprite m_faceRight;
	Sprite m_poseSleep;
	Sprite m_poseDeath;

	Texture& GetTexture(const char* name)
	{
		if (m_faceUp.m_name == name)
			return m_faceUp.m_texture;
		else if (m_faceDown.m_name == name)
			return m_faceDown.m_texture;
		else if (m_faceLeft.m_name == name)
			return m_faceLeft.m_texture;
		else if (m_faceRight.m_name == name)
			return m_faceRight.m_texture;
		else if (m_poseSleep.m_name == name)
			return m_poseSleep.m_texture;
		else if (m_poseDeath.m_name == name)
			return m_poseDeath.m_texture;

		return m_faceLeft.m_texture;
	}
};
