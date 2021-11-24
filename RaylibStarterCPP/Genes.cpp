#include "Genes.h"

Genes::Genes()
{
	m_diet = DietClass::Omnivore;
	m_detectionRange = 60;
	m_maxHealth = 100;
	m_maxSpeed = 75;
	m_maxHunger = 100;
	m_maxThirst = 100;
	m_maxEnergy = 100;
}

Genes::Genes(DietClass diet, float detectionRange, float maxHealth, float maxSpeed, float maxHunger, float maxThirst, float maxEnergy)
{
	m_diet = diet;
	m_detectionRange = detectionRange;
	m_maxHealth = maxHealth;
	m_maxSpeed = maxSpeed;
	m_maxHunger = maxHunger;
	m_maxThirst = maxThirst;
	m_maxEnergy = maxEnergy;
}
