#pragma once

enum class DietClass
{
	Carnivore,
	Herbivore,
	Omnivore
};

struct Genes
{
	// Diet type of the creature
	DietClass m_diet;
	// Distance of sight
	float m_detectionRange;
	// Health
	float m_maxHealth;
	// Max movement speed
	float m_maxSpeed;
	// Hunger
	float m_maxHunger;
	// Thirst
	float m_maxThirst;
	// Energy
	float m_maxEnergy;

	Genes();
	Genes(DietClass diet, float detectionRange, float maxHealth, float maxSpeed, float maxHunger, float maxThirst, float maxEnergy);
};