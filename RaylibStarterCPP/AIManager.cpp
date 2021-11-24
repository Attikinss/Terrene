#include "AIManager.h"
#include "Agent.h"
#include "UIManager.h"

using namespace std;

AIManager* AIManager::s_instance = nullptr;

AIManager::AIManager()
{
	
}

AIManager::~AIManager()
{
	for (Agent* agent : m_sheep)
	{
		delete agent;
		agent = nullptr;
	}

	for (Agent* agent : m_wolves)
	{
		delete agent;
		agent = nullptr;
	}
}

void AIManager::Create()
{
	if (s_instance == nullptr)
		s_instance = new AIManager();
}

void AIManager::Destroy()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

void AIManager::Update()
{
	for (Agent* sheep : m_sheep)
	{
		sheep->Update();
		if (sheep->m_awaitingDeletion)
		{
			Agent* temp = sheep;
			vector<Agent*>::iterator it = find(m_sheep.begin(), m_sheep.end(), sheep);
			
			if (it != m_sheep.end())
				m_sheep.erase(it);

			delete temp;
			temp = nullptr;
		}
	}

	for (Agent* wolf : m_wolves)
	{
		wolf->Update();
		if (wolf->m_awaitingDeletion)
		{
			Agent* temp = wolf;
			vector<Agent*>::iterator it = find(m_wolves.begin(), m_wolves.end(), wolf);
			
			if (it != m_wolves.end())
				m_wolves.erase(it);

			delete temp;
			temp = nullptr;
		}
	}
}

void AIManager::Draw()
{
	for (Agent* sheep : m_sheep)
	{
		UIManager::GetInstance()->HighlightAgent(sheep);
		sheep->Draw();
	}

	for (Agent* wolf : m_wolves)
	{
		UIManager::GetInstance()->HighlightAgent(wolf);
		wolf->Draw();
	}
}

void AIManager::DrawDebug()
{
	for (Agent* sheep : m_sheep)
		if(sheep->m_animal.m_alive)
			sheep->DrawDebug();

	for (Agent* wolf : m_wolves)
		if (wolf->m_animal.m_alive)
			wolf->DrawDebug();
}

void AIManager::AddSheep(Agent* sheep)
{
	m_sheep.push_back(sheep);
}

void AIManager::AddWolf(Agent* wolf)
{
	m_wolves.push_back(wolf);
}

bool AIManager::NoAgents()
{
	return (m_sheep.empty() && m_wolves.empty());
}

void AIManager::DeleteAgent(Agent* agent)
{
	if (agent->m_animal.m_type == AnimalSelection::Sheep)
	{
		vector<Agent*>::iterator it = find(m_sheep.begin(), m_sheep.end(), agent);

		if (it != m_sheep.end())
			m_sheep.erase(it);

		delete agent;
		agent = nullptr;
	}
	else if (agent->m_animal.m_type == AnimalSelection::Wolf)
	{
		vector<Agent*>::iterator it = find(m_wolves.begin(), m_wolves.end(), agent);

		if (it != m_wolves.end())
			m_wolves.erase(it);

		delete agent;
		agent = nullptr;
	}
}