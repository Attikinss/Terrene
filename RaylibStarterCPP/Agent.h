#pragma once
#include <vector>
#include <algorithm>
#include "raylib.h"
#include "Node.h"
#include "GameManager.h"
#include "Genes.h"
#include "Blackboard.h"
#include "Animal.h"

class DecisionTree;
class DTNode;
class UIManager;

class Agent
{
	friend class UIManager;
	friend class DecisionTree;
	friend class DTNode;
	friend class Blackboard;

public:
	// UI Stuff
	bool m_selected = false;
	bool m_mouseOver = false;
	const char* m_currTaskText;

	float m_decayTime = 30; // Time it takes for a dead animal to be deleted
	bool m_awaitingDeletion = false;
	Animal m_animal;
	Agent* m_prey = nullptr;
	Vec2 m_position = Vec2();
	Vec2 m_velocity = Vec2();

	Agent(Node* initPos, AnimalSelection animal, Genes initGenes);
	~Agent();

	// General functions
	void Init();
	void Update();
	void Draw();
	void DrawDebug();

private:
	DecisionTree* m_dTree = nullptr;
	GameManager* m_gameMgr = nullptr;
	Blackboard* m_blackboard = nullptr;

	bool m_stuck = false;

	// Stats
	bool m_drinking = false;
	bool m_eating = false;
	bool m_sleeping = false;

	void UpdateStats();
	void MouseOver();
	void Unstick();
	void Kill();

	// Node info
	Node* m_currPosNode = nullptr;
	Node* m_startNode = nullptr;
	Node* m_target = nullptr;

	// Path info
	std::vector<Vec2> m_path;
	Vec2 m_targetPos = Vec2();

	// DT Condtition Functions
	bool EnemyNear();
	bool PreyInSight();
	bool AtPrey();
	void ChasePrey();
	void Attack();
	bool IsTired();
	bool IsThirsty();
	bool ThirstIsPriority();
	bool WaterInSight();
	bool AtWater();
	bool IsHungry();
	bool HungerIsPriority();
	bool FoodInSight();
	bool AtFood();

	// DT Action functions
	void Flee();
	void Sleep();
	void Wander();
	void MoveToWater();
	void Drink();
	void MoveToFood();
	void Eat();

	// A* pathfinding related functions
	void GetRandomPos();
	void GetRandomPos(Vec2 closestEnemyPos);
	void SetPath(std::vector<Vec2> nodePositions);
	void AppendToPath(std::vector<Vec2> nodePositions);
	void ClearPath();
	void Navigate();
	void CalculateAStarPath();
};