#pragma once
#include <vector>

class Agent;

class AIManager
{
public:
	static void Create();
	static void Destroy();
	void Update();
	void Draw();
	void DrawDebug();
	static AIManager* GetInstance() { return s_instance; }

	void AddSheep(Agent* sheep);
	void AddWolf(Agent* wolf);
	bool NoAgents();
	void DeleteAgent(Agent* agent);
	std::vector<Agent*> GetSheep() { return m_sheep; }
	std::vector<Agent*> GetWolves() { return m_wolves; }

private:
	static AIManager* s_instance;
	 std::vector<Agent*> m_sheep;
	 std::vector<Agent*> m_wolves;

	AIManager();
	~AIManager();
};