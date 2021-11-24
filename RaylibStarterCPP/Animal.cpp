#include "Animal.h"

Animal::Animal(Vec2 initPos, Genes genes)
{
	m_texturePos = initPos;
	m_genes = genes;
}

Animal::~Animal()
{
	
}

void Animal::Init()
{
	// Set stats
	m_alive = true;
	m_health = m_genes.m_maxHealth;
	m_speed = m_genes.m_maxSpeed;
	m_thirst = m_genes.m_maxThirst;
	m_hunger = m_genes.m_maxHunger;
	m_energy = m_genes.m_maxEnergy;

	switch (m_type)
	{
		case AnimalSelection::Sheep:
		{
			SetName("Sheep");
			SetAnimalSprites("Sheep");
			m_attackCooldown = 0;
			m_attackDmg = 0;
			break;
		}
		case AnimalSelection::Wolf:
		{
			SetName("Wolf");
			SetAnimalSprites("Wolf");
			m_attackCooldown = 1.0f;
			m_attackDmg = 250.0f;
			break;
		}
		case AnimalSelection::Rabbit: // Not used
		{
			SetName("Rabbit");
			SetAnimalSprites("Rabbit");
			m_attackCooldown = 0;
			m_attackDmg = 0;
			break;
		}
		default:
		{
			SetName("Unknown");
			m_attackCooldown = 0;
			m_attackDmg = 0;
			break;
		}
	}
}

void Animal::Update()
{
	std::stringstream temp;

	temp << "Health: " << (std::floor(m_health * 10 + 0.5f) / 10) << "\n";
	temp << "Thirst: " << (std::floor(m_thirst * 10 + 0.5f) / 10) << "\n";
	temp << "Hunger: " << (std::floor(m_hunger * 10 + 0.5f) / 10) << "\n";
	temp << "Energy: " << (std::floor(m_energy * 10 + 0.5f) / 10) << "\n";

	m_stats = temp.str().c_str();
}

void Animal::SetPosition(Vec2 pos)
{
	m_texturePos = { pos.x - m_currTexture->width / 2 + 5, pos.y - m_currTexture->height / 2 + 5 };
}

void Animal::SetAnimalSprites(const char* animal)
{
	m_sprites = TextureManager::GetInstance()->GetSpriteWrapper(animal);
}

void Animal::SetName(const char* name)
{
	n_name = name;
}

const char* Animal::GetName()
{
	return n_name;
}

// Only supports - [up] [down] [left] [right]
void Animal::ChangeSprite(const char* spriteName)
{
	m_currTexture = &m_sprites.GetTexture(spriteName);
}

void Animal::Draw()
{
	DrawTexture(*m_currTexture, (int)m_texturePos.x, (int)m_texturePos.y, WHITE);
}
