#include "Blackboard.h"
#include "Agent.h"

void Blackboard::LinkToAgent(Agent* self)
{
	Self = self;
}

void Blackboard::Update()
{
	if (Self == nullptr)
		return;

	SetClosestWolf();
	SetClosestSheep();
	SetClosestWaterNode();
	SetClosestFoodNode();
	SetClosestDeadPrey();
}

Agent* Blackboard::GetClosestWolf()
{
	if (m_closestWolf != nullptr)
		return m_closestWolf;

	return nullptr;
}

void Blackboard::SetClosestWolf()
{
	std::vector<Agent*> wolves = AIManager::GetInstance()->GetWolves();
	Agent* closestWolf = nullptr;

	for (Agent* currWolf : wolves)
	{
		if (Self->m_position.Distance(currWolf->m_position) <= Self->m_animal.m_genes.m_detectionRange && currWolf->m_animal.m_alive)
		{
			if (closestWolf == nullptr)
				closestWolf = currWolf;
			else
			{
				if (Self->m_position.Distance(closestWolf->m_position) <= Self->m_position.Distance(currWolf->m_position))
					closestWolf = currWolf;
			}
		}
	}

	if (closestWolf != nullptr)
	{
		m_closestWolf = closestWolf;
	}
	else
		m_closestWolf = nullptr;
}

Agent* Blackboard::GetClosestSheep()
{
	if (m_closestSheep != nullptr)
		return m_closestSheep;

	return nullptr;
}
Agent* Blackboard::GetClosestDeadPrey()
{
	if (m_closestDeadPrey != nullptr)
		return m_closestDeadPrey;

	return nullptr;
}

void Blackboard::SetClosestDeadPrey()
{
	std::vector<Agent*> prey = AIManager::GetInstance()->GetSheep();
	Agent* closestPrey = nullptr;

	for (Agent* currPrey : prey)
	{
		if (Self->m_position.Distance(currPrey->m_position) <= Self->m_animal.m_genes.m_detectionRange && !currPrey->m_animal.m_alive)
		{
			if (closestPrey == nullptr)
				closestPrey = currPrey;
			else
			{
				if (Self->m_position.Distance(closestPrey->m_position) <= Self->m_position.Distance(currPrey->m_position))
					closestPrey = currPrey;
			}
		}
	}

	if (closestPrey != nullptr)
		m_closestDeadPrey = closestPrey;
	else
		m_closestDeadPrey = nullptr;
}

void Blackboard::SetClosestSheep()
{
	std::vector<Agent*> sheep = AIManager::GetInstance()->GetSheep();
	Agent* closestSheep = nullptr;

	for (Agent* currSheep : sheep)
	{
		if (Self->m_position.Distance(currSheep->m_position) <= Self->m_animal.m_genes.m_detectionRange && currSheep->m_animal.m_alive)
		{
			if (closestSheep == nullptr)
				closestSheep = currSheep;
			else
			{
				if (Self->m_position.Distance(closestSheep->m_position) <= Self->m_position.Distance(currSheep->m_position))
					closestSheep = currSheep;
			}
		}
	}

	if (closestSheep != nullptr)
		m_closestSheep = closestSheep;
	else
		m_closestSheep = nullptr;
}

Node* Blackboard::GetClosestWaterNode()
{
	if (m_closestWaterNode != nullptr)
		return m_closestWaterNode;

	return nullptr;
}

void Blackboard::SetClosestWaterNode()
{
	std::vector<Node*> waterNodes = GameManager::GetInstance()->GetWaterNodes();
	Node* closestWaterNode = nullptr;

	for (Node* currNode : waterNodes)
	{
		if (Self->m_position.Distance(currNode->m_position) <= Self->m_animal.m_genes.m_detectionRange)
		{
			if (closestWaterNode == nullptr)
				closestWaterNode = currNode;
			else
			{
				if (Self->m_position.Distance(closestWaterNode->m_position) >= Self->m_position.Distance(currNode->m_position))
					closestWaterNode = currNode;
			}
		}
	}

	if (closestWaterNode != nullptr)
		m_closestWaterNode = closestWaterNode;
	else
		m_closestWaterNode = nullptr;
}

Node* Blackboard::GetClosestFoodNode()
{
	if (m_closestFoodNode != nullptr)
		return m_closestFoodNode;

	return nullptr;
}

void Blackboard::SetClosestFoodNode()
{
	std::vector<Node*> foodNodes = GameManager::GetInstance()->GetFoodNodes();
	Node* closestFoodNode = nullptr;

	for (Node* currNode : foodNodes)
	{
		if (Self->m_position.Distance(currNode->m_position) <= Self->m_animal.m_genes.m_detectionRange)
		{
			if (closestFoodNode == nullptr)
				closestFoodNode = currNode;
			else
			{
				if (Self->m_position.Distance(closestFoodNode->m_position) >= Self->m_position.Distance(currNode->m_position))
					closestFoodNode = currNode;
			}
		}
	}

	if (closestFoodNode != nullptr)
		m_closestFoodNode = closestFoodNode;
	else
		m_closestFoodNode = nullptr;
}