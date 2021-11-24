#pragma once
#include "Node.h"
#include "GameManager.h"

class Agent;

class Blackboard
{
private:
	// The agent this blackboard is attached to
	Agent* Self = nullptr;
	// Closest wolf to agent
	Agent* m_closestWolf = nullptr;
	// Closest dead animal to agent
	Agent* m_closestDeadPrey = nullptr;
	// Closest sheep to agent
	Agent* m_closestSheep = nullptr;
	// Closest water node to agent
	Node* m_closestWaterNode = nullptr;
	// Closest food node to agent
	Node* m_closestFoodNode = nullptr;

public:
	void LinkToAgent(Agent* self);
	void Update();

	Agent* GetClosestWolf();
	void SetClosestWolf();

	Agent* GetClosestSheep();
	void SetClosestSheep();

	Agent* GetClosestDeadPrey();
	void SetClosestDeadPrey();

	Node* GetClosestWaterNode();
	void SetClosestWaterNode();

	Node* GetClosestFoodNode();
	void SetClosestFoodNode();
};