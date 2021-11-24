#pragma once
#include <sstream>
#include "CustomMath.h"
#include "raylib.h"
#include "Genes.h"
#include "TextureManager.h"

enum class DietType
{
	Herbivore,
	Carnivore,
	Omnivore
};

enum class AnimalSelection
{
	Sheep,
	Wolf,
	Rabbit
};

class Animal
{
protected:
	// Basic info
	const char* n_name;

	// Visuals
	Texture* m_currTexture = nullptr;
	SpriteWrapper m_sprites;
	Vec2 m_texturePos;

public:
	std::string m_stats;
	// Type of animal
	AnimalSelection m_type;
	// Diet type of animal
	DietType m_diet;
	// Genes of the animal (max values)
	Genes m_genes;

	bool m_alive;
	// Health
	float m_health;
	// Thirst
	float m_thirst;
	// Hunger
	float m_hunger;
	// Energy
	float m_energy;
	// Movement speed
	float m_speed;
	// Attack damage
	float m_attackDmg;
	// Attack cooldown time
	float m_attackCooldown;

	Animal() {}
	Animal(Vec2 initPos, Genes genes);
	virtual ~Animal();

	void Init();
	void Update();
	void SetPosition(Vec2 pos);
	void SetAnimalSprites(const char* animal);
	const char* GetName();
	void SetName(const char* name);
	void ChangeSprite(const char* direction);
	void Draw();
};

class Sheep : public Animal
{
public:
	Sheep(Vec2 initPos, Genes genes);
};

class Wolf : public Animal
{
public:
	Wolf(Vec2 initPos, Genes genes);
};