#include "Agent.h"
#include "DecisionTree.h"
#include "DTNode.h"
#include "UIManager.h"
#include <iostream>

using namespace std;

Agent::Agent(Node* initPos, AnimalSelection animal, Genes initGenes)
{
	m_position = initPos->m_position;
	m_animal.m_type = animal;
	m_animal.m_genes = initGenes;

	Init();
}

Agent::~Agent()
{
	m_currPosNode = nullptr;
	m_startNode = nullptr;
	ClearPath();
	delete m_dTree;
	delete m_blackboard;
}

void Agent::Init()
{
	// Get pointer to game manager
	m_gameMgr = GameManager::GetInstance();

	// Initialise animal details
	m_animal.Init();

	// Link blackboard to this
	m_blackboard = new Blackboard();
	m_blackboard->LinkToAgent(this);
	
	// Initialise decision tree
	m_dTree = new DecisionTree();

#pragma region <[ Setup decision tree ]>

	// ** CONDITIONS SHARED BY ALL ANIMAL TYPES **
	// Energy
	Condition* c_tired = new Condition("Tired", &Agent::IsTired, this, m_dTree);

	// Water
	Condition* c_thirsty = new Condition("Thirsty", &Agent::IsThirsty, this, m_dTree);
	Condition* c_hungerIsPriority = new Condition("HungerPriority", &Agent::HungerIsPriority, this, m_dTree);
	Condition* c_waterInSight = new Condition("WaterInSight", &Agent::WaterInSight, this, m_dTree);
	Condition* c_atWater = new Condition("AtWater", &Agent::AtWater, this, m_dTree);

	// Food
	Condition* c_hungry = new Condition("Hungry", &Agent::IsHungry, this, m_dTree);
	Condition* c_thirstIsPriority = new Condition("ThirstIsPriority", &Agent::ThirstIsPriority, this, m_dTree);
	Condition* c_foodInSight = new Condition("FoodInSight", &Agent::FoodInSight, this, m_dTree);
	Condition* c_atFood = new Condition("AtFood", &Agent::AtFood, this, m_dTree);

	// ** ACTIONS SHARED BY ALL ANIMAL TYPES**
	Leaf* a_sleep = new Leaf("Sleep", &Agent::Sleep, this, m_dTree);
	Leaf* a_wander = new Leaf("Wander", &Agent::Wander, this, m_dTree);

	// Water
	Leaf* a_moveToWater = new Leaf("MoveToWater", &Agent::MoveToWater, this, m_dTree);
	Leaf* a_drink = new Leaf("Drink", &Agent::Drink, this, m_dTree);

	// Food
	Leaf* a_moveToFood = new Leaf("MoveToFood", &Agent::MoveToFood, this, m_dTree);
	Leaf* a_eat = new Leaf("Eat", &Agent::Eat, this, m_dTree);

	if (m_animal.m_type == AnimalSelection::Wolf)
	{
		// Conditions and actions specifically for the wolves
		Condition* root = new Condition("Entry", &Agent::PreyInSight, this, m_dTree);
		Condition* c_preyInSight = new Condition("PreyInSight", &Agent::PreyInSight, this, m_dTree);
		Condition* c_atPrey = new Condition("AtPrey", &Agent::AtPrey, this, m_dTree);
		Leaf* a_chasePrey = new Leaf("ChasePrey", &Agent::ChasePrey, this, m_dTree);
		Leaf* a_attack = new Leaf("Attack", &Agent::Attack, this, m_dTree);

		// Prey nearby?
		root->SetSuccessChild(c_atPrey);
		root->SetFailChild(c_thirsty);

		// At prey?
		c_atPrey->SetSuccessChild(a_attack);
		c_atPrey->SetFailChild(a_chasePrey);

		// Am thirsty?
		c_thirsty->SetSuccessChild(c_thirstIsPriority);
		c_thirsty->SetFailChild(c_hungry);

		// Thirst priority?
		c_thirstIsPriority->SetSuccessChild(c_waterInSight);
		c_thirstIsPriority->SetFailChild(c_hungry);

		// Water nearby?
		c_waterInSight->SetSuccessChild(c_atWater);
		c_waterInSight->SetFailChild(c_hungry); // Revaluate priority to hunger here

		// At water?
		c_atWater->SetSuccessChild(a_drink);
		c_atWater->SetFailChild(a_moveToWater);

		// Am hungry?
		c_hungry->SetSuccessChild(c_hungerIsPriority);
		c_hungry->SetFailChild(c_tired);

		// Hunger priority?
		c_hungerIsPriority->SetSuccessChild(c_foodInSight);
		c_hungerIsPriority->SetFailChild(c_tired);

		// Food nearby?
		c_foodInSight->SetSuccessChild(c_atFood);
		c_foodInSight->SetFailChild(c_tired); // Revaluate priority to water here

		// At food?
		c_atFood->SetSuccessChild(a_eat);
		c_atFood->SetFailChild(a_moveToFood);

		// Am tired?
		c_tired->SetSuccessChild(a_sleep);
		c_tired->SetFailChild(a_wander);

		m_dTree->SetRoot(root);
	}
	if (m_animal.m_type == AnimalSelection::Sheep)
	{
		// Conditions and actions specifically for the sheep
		Condition* root = new Condition("Entry", &Agent::EnemyNear, this, m_dTree);
		Leaf* a_flee = new Leaf("Flee", &Agent::Flee, this, m_dTree);

		// Enemy near?
		root->SetSuccessChild(a_flee);
		root->SetFailChild(c_thirsty);

		// Am thirsty?
		c_thirsty->SetSuccessChild(c_thirstIsPriority);
		c_thirsty->SetFailChild(c_hungry);

		// Thirst priority?
		c_thirstIsPriority->SetSuccessChild(c_waterInSight);
		c_thirstIsPriority->SetFailChild(c_hungry);

		// Water nearby?
		c_waterInSight->SetSuccessChild(c_atWater);
		c_waterInSight->SetFailChild(c_hungry); // Revaluate priority to hunger here

		// At water?
		c_atWater->SetSuccessChild(a_drink);
		c_atWater->SetFailChild(a_moveToWater);

		// Am hungry?
		c_hungry->SetSuccessChild(c_hungerIsPriority);
		c_hungry->SetFailChild(c_tired);

		// Hunger priority?
		c_hungerIsPriority->SetSuccessChild(c_foodInSight);
		c_hungerIsPriority->SetFailChild(c_tired);

		// Food nearby?
		c_foodInSight->SetSuccessChild(c_atFood);
		c_foodInSight->SetFailChild(c_tired); // Revaluate priority to water here

		// At food?
		c_atFood->SetSuccessChild(a_eat);
		c_atFood->SetFailChild(a_moveToFood);

		// Am tired?
		c_tired->SetSuccessChild(a_sleep);
		c_tired->SetFailChild(a_wander);
		
		m_dTree->SetRoot(root);
	}

#pragma endregion
}

void Agent::Update()
{
	if (!m_animal.m_alive)
	{
		m_decayTime -= GetFrameTime();
		m_decayTime = Clamp(m_decayTime, 0, 30.0f);
		if (m_decayTime <= 0)
			m_awaitingDeletion = true;

		m_animal.ChangeSprite("Dead");
		m_animal.Update();
		m_currTaskText = "Dead";
		MouseOver();
		return;
	}

	if (m_stuck)
	{
		Unstick();
	}

	m_currPosNode = &m_gameMgr->m_map->nodes[(int)m_position.x / TILE_SIZE][(int)m_position.y / TILE_SIZE];
	m_blackboard->Update();

	m_currTaskText = "";
	UpdateStats();
	MouseOver();

	m_dTree->Traverse();
}

void Agent::UpdateStats()
{
	float deltaTime = GameManager::GetInstance()->DeltaTime() * 2;
	float movementPenalty = m_animal.m_speed * (deltaTime * deltaTime);	

	if (!m_drinking)
	{
		m_animal.m_thirst -= deltaTime;
		m_animal.m_thirst = Clamp(m_animal.m_thirst, 0, m_animal.m_genes.m_maxThirst);
	}
	if (!m_eating)
	{
		m_animal.m_hunger -= deltaTime;
		m_animal.m_hunger = Clamp(m_animal.m_hunger, 0, m_animal.m_genes.m_maxHunger);
	}

	if (!m_sleeping)
	{
		m_animal.m_energy -= deltaTime;
		m_animal.m_energy = Clamp(m_animal.m_energy, 0, m_animal.m_genes.m_maxEnergy);
	}

	// Update sprite facing direction based off velocity
	if (Abs(m_velocity.x) >= Abs(m_velocity.y))
	{
		if (m_velocity.x > 0)
			m_animal.ChangeSprite("Right");
		else
			m_animal.ChangeSprite("Left");
	}
	else
	{
		if (m_velocity.y > 0)
			m_animal.ChangeSprite("Down");
		else
			m_animal.ChangeSprite("Up");
	}
	
	if (m_sleeping)
		m_animal.ChangeSprite("Sleep");

	m_animal.SetPosition(m_position);
	m_animal.Update();
}

void Agent::MouseOver()
{
	if (m_gameMgr->m_overrideMouseState)
	{
		if (m_position.Distance(m_gameMgr->MousePosition()) <= TILE_SIZE / 2)
		{
			m_mouseOver = true;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				m_selected = true;
		}
		else
		{
			m_mouseOver = false;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				m_selected = false;
		}

		if (m_mouseOver)
		{
			if (m_selected)
			{
				m_gameMgr->m_mouseState = MouseState::Delete;
				if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
					m_awaitingDeletion = true;
			}
		}
		else
			m_gameMgr->m_mouseState = MouseState::Select;
	}
}

void Agent::Unstick()
{
	for (Node* neighbour : m_currPosNode->m_neighbours)
	{
		if (!neighbour->m_obstacle)
		{
			m_position = neighbour->m_position;
			m_stuck = false;
			break;
		}
	}
}

bool Agent::EnemyNear()
{
	if ((m_blackboard->GetClosestWolf() != nullptr))
	{
		m_animal.m_speed = m_animal.m_genes.m_maxSpeed;
		m_sleeping = false;
		m_eating = false;
		m_drinking = false;
		return true;
	}

	m_animal.m_speed = m_animal.m_genes.m_maxSpeed / 2;

	return false;
}

bool Agent::PreyInSight()
{
	if (m_blackboard->GetClosestSheep() != nullptr)
	{
		m_animal.m_speed = m_animal.m_genes.m_maxSpeed;

		if (m_prey == nullptr)
			m_prey = m_blackboard->GetClosestSheep();

		m_sleeping = false;
		m_eating = false;
		m_drinking = false;
		return true;
	}

	m_prey = nullptr;
	m_animal.m_speed = m_animal.m_genes.m_maxSpeed / 2;

	return false;
}

bool Agent::AtPrey()
{
	if (m_prey != nullptr)
	{
		if (m_position.Distance(m_prey->m_position) <= TILE_SIZE / 2)
			return true;

		m_sleeping = false;
		m_eating = false;
		m_drinking = false;
	}

	return false;
}

void Agent::ChasePrey()
{
	// If sheep actually exists and is in a short enough range
	if (m_prey != nullptr)
	{
		m_sleeping = false;
		m_eating = false;
		m_drinking = false;

		if (m_position.Distance(m_prey->m_position) <= TILE_SIZE * 3)
		{
			if (!m_path.empty())
				ClearPath();

			m_targetPos = m_prey->m_position;
			Navigate();
		}
		else
		{
			if (m_target != m_prey->m_currPosNode)
			{
				ClearPath();
				m_target = m_prey->m_currPosNode;
				m_startNode = m_currPosNode;
				CalculateAStarPath();
			}
			else
				Navigate();
		}

		m_currTaskText = "Hunting";
	}
	else
		m_currTaskText = "Chasing ghosts???";
}

void Agent::Attack()
{
	float cooldownTime = m_animal.m_attackCooldown;

	if (cooldownTime == 1.0f)
	{
		m_prey->m_animal.m_health -= m_animal.m_attackDmg * GetFrameTime();

		if (m_prey->m_animal.m_health <= 0)
		{
			m_prey->Kill();
			m_prey = nullptr;
		}

		cooldownTime -= GetFrameTime();
	}
	else
	{
		m_animal.m_speed = 0;
		cooldownTime -= GetFrameTime();
		cooldownTime = Clamp(cooldownTime, 0.0f, 1.0f);

		if (cooldownTime == 0.0f)
			cooldownTime = 1.0f;
	}

	m_currTaskText = "Hunting";
}

bool Agent::IsTired()
{
	if (m_sleeping)
		return true;

	return m_animal.m_energy < m_animal.m_genes.m_maxEnergy / 2.0f;
}

bool Agent::IsThirsty()
{
	if (m_drinking)
		return true;

	return m_animal.m_thirst < m_animal.m_genes.m_maxThirst / 1.5f;
}

bool Agent::ThirstIsPriority()
{
	if ((WaterInSight() && IsThirsty()) || (WaterInSight() && m_animal.m_thirst < m_animal.m_hunger) || m_drinking)
		return true;
	else if (FoodInSight() && m_animal.m_thirst > m_animal.m_hunger || m_eating)
	{
		m_drinking = false;
		return false;
	}
		
	m_drinking = false;
	return false;
}

bool Agent::WaterInSight()
{
	return (m_blackboard->GetClosestWaterNode() != nullptr);
}

bool Agent::AtWater()
{
	if (m_blackboard->GetClosestWaterNode() != nullptr)
	{
		if (m_position.Distance(m_blackboard->GetClosestWaterNode()->m_position) <= TILE_SIZE)
			return true;
	}

	return false;
}

bool Agent::IsHungry()
{
	if (m_eating)
		return true;

	return m_animal.m_hunger < m_animal.m_genes.m_maxHunger / 2.0f;
}

bool Agent::HungerIsPriority()
{
	// If agent can see food
	if ((FoodInSight() && !IsThirsty() && IsHungry()) || (FoodInSight() && m_animal.m_hunger < m_animal.m_thirst) || m_eating)
		return true;
	// If agent can see water and it's thirst level is lower than it's hunger
	else if (WaterInSight() && m_animal.m_hunger > m_animal.m_thirst || m_drinking)
	{
		m_eating = false;
		return false;
	}

	m_eating = false;
	return false;
}

bool Agent::FoodInSight()
{
	if (m_animal.m_type == AnimalSelection::Sheep && m_blackboard->GetClosestFoodNode() != nullptr)
		return true;
	else if (m_animal.m_type == AnimalSelection::Wolf && m_blackboard->GetClosestDeadPrey() != nullptr)
		return true;

	m_eating = false;
	return false;
}

bool Agent::AtFood()
{
	if (m_animal.m_type == AnimalSelection::Sheep)
	{
		if (m_blackboard->GetClosestFoodNode() != nullptr)
		{
			if (m_position.Distance(m_blackboard->GetClosestFoodNode()->m_position) <= TILE_SIZE)
				return true;
		}
	}
	else if (m_animal.m_type == AnimalSelection::Wolf)
	{
		if (m_blackboard->GetClosestDeadPrey() != nullptr)
		{
			if (m_position.Distance(m_blackboard->GetClosestDeadPrey()->m_position) <= TILE_SIZE)
				return true;
		}
	}

	m_eating = false;
	return false;
}

void Agent::Flee()
{
	m_sleeping = false;
	m_drinking = false;
	m_eating = false;

	if (m_path.empty())
	{
		if (m_currPosNode->m_obstacle)
		{
			m_currTaskText = "Stuck";
			m_stuck = true;
			return;
		}

		GetRandomPos();
		GetRandomPos(m_blackboard->GetClosestWolf()->m_position);
		m_startNode = m_currPosNode;
		CalculateAStarPath();
	}
	else
	{
		Navigate();
	}

	m_currTaskText = "Fleeing";
}

void Agent::Sleep()
{
	if (!m_path.empty())
		ClearPath();

	if (m_animal.m_energy < m_animal.m_genes.m_maxEnergy)
	{
		m_sleeping = true;

		// Replenish energy
		m_animal.m_energy += 10 * GameManager::GetInstance()->DeltaTime();

		// Cap energy
		if (m_animal.m_energy > m_animal.m_genes.m_maxEnergy)
		{
			m_animal.m_energy = m_animal.m_genes.m_maxEnergy;
			m_sleeping = false;
		}
	}

	m_currTaskText = "Sleeping";
}

void Agent::Wander()
{
	if (m_path.empty())
	{
		if (m_currPosNode->m_obstacle)
		{
			m_currTaskText = "Stuck";
			m_stuck = true;
			return;
		}

		GetRandomPos();
		m_startNode = m_currPosNode;
		CalculateAStarPath();
	}
	else
	{
		Navigate();
		m_currTaskText = "Wandering";
	}

}

void Agent::MoveToWater()
{
	// if: target node isn't closest water node
	//		Clear path
	//		Set target node to closest water node
	//		A* Calculation
	// else:
	//		Traverse path
	
	m_drinking = false;
	m_eating = false;
	m_sleeping = false;

	if (m_target != m_blackboard->GetClosestWaterNode())
	{
		if (!m_path.empty())
			ClearPath();

		m_target = m_blackboard->GetClosestWaterNode();
		m_startNode = m_currPosNode;
		CalculateAStarPath();
	}
	else
		Navigate();

	m_currTaskText = "Finding water";
}

void Agent::Drink()
{
	if (!m_path.empty())
		ClearPath();

	if (m_animal.m_thirst < m_animal.m_genes.m_maxThirst)
	{
		m_drinking = true;
		// Replenish thirst
		m_animal.m_thirst += 10 * GameManager::GetInstance()->DeltaTime();

		// Cap thirst
		if (m_animal.m_thirst > m_animal.m_genes.m_maxThirst)
		{
			m_animal.m_thirst = m_animal.m_genes.m_maxThirst;
			m_drinking = false;
		}
	}

	m_currTaskText = "Drinking";
}

void Agent::MoveToFood()
{
	// if: target node isn't closest food node
	//		Clear path
	//		Set target node to closest food node
	//		A* Calculation
	// else:
	//		Traverse path

	m_drinking = false;
	m_eating = false;
	m_sleeping = false;

	if (m_animal.m_type == AnimalSelection::Sheep)
	{
		if (m_target != m_blackboard->GetClosestFoodNode())
		{
			if (!m_path.empty())
				ClearPath();

			m_target = m_blackboard->GetClosestFoodNode();
			m_startNode = m_currPosNode;
			CalculateAStarPath();
		}
		else
			Navigate();
	}
	else if (m_animal.m_type == AnimalSelection::Wolf)
	{
		if (m_target != m_blackboard->GetClosestDeadPrey()->m_currPosNode)
		{
			if (!m_path.empty())
				ClearPath();

			m_target = m_blackboard->GetClosestDeadPrey()->m_currPosNode;
			m_startNode = m_currPosNode;
			CalculateAStarPath();
		}
		else
			Navigate();
	}

	m_currTaskText = "Finding food";
}

void Agent::Eat()
{
	if (!m_path.empty())
		ClearPath();

	if (m_animal.m_hunger < m_animal.m_genes.m_maxHunger)
	{
		m_eating = true;
		// Replenish hunger
		m_animal.m_hunger += 10 * GameManager::GetInstance()->DeltaTime();
		
		// Cap hunger
		if (m_animal.m_hunger > m_animal.m_genes.m_maxHunger)
		{
			m_animal.m_hunger = m_animal.m_genes.m_maxHunger;
			m_eating = false;
		}
	}

	m_currTaskText = "Eating";
}

void Agent::Kill()
{
	m_animal.m_alive = false;
	m_animal.m_health = 0;
	m_animal.m_energy = 0;
	m_animal.m_hunger = 0;
	m_animal.m_thirst = 0;
	m_animal.m_speed = 0;
}

void Agent::SetPath(vector<Vec2> nodePositions)
{
	m_path.clear();

	for (size_t i = nodePositions.size(); i > 0; i--)
		m_path.push_back(nodePositions[i - 1]);
}

void Agent::AppendToPath(vector<Vec2> nodePositions)
{
	for (size_t i = nodePositions.size(); i > 0; i--)
		m_path.push_back(nodePositions[i - 1]);
}

void Agent::ClearPath()
{
	m_path.clear();
	m_target = nullptr;
}

void Agent::GetRandomPos()
{
	m_target = nullptr;

	while (m_target == nullptr)
	{
		// Get random x pos
		int randX = rand();
		if (randX % 2 == 0)
			randX = (1 + (rand() % (int)((m_animal.m_genes.m_detectionRange / TILE_SIZE) - 1 + 1)));
		else							
			randX = (1 + (rand() % (int)((m_animal.m_genes.m_detectionRange / TILE_SIZE) - 1 + 1))) * -1;

		// Add current position to rand x pos
		randX += (int)m_currPosNode->m_position.x / TILE_SIZE;

		// Clamp x pos
		if (randX < 0)
			randX = 0;
		if (randX > m_gameMgr->m_map->gridSizeX - 1)
			randX = m_gameMgr->m_map->gridSizeX - 1;

		// Get random y pos
		int randY = rand();
		if (randY % 2 == 0)
			randY = (1 + (rand() % (int)((m_animal.m_genes.m_detectionRange / TILE_SIZE) - 1 + 1)));
		else
			randY = (1 + (rand() % (int)((m_animal.m_genes.m_detectionRange / TILE_SIZE) - 1 + 1))) * -1;

		// Add current position to rand y pos
		randY += (int)m_currPosNode->m_position.y / TILE_SIZE;

		// Clamp y pos
		if (randY < 0)
			randY = 0;
		if (randY > m_gameMgr->m_map->gridSizeY - 1)
			randY = m_gameMgr->m_map->gridSizeY - 1;

		// Assign new target node
		m_target = &m_gameMgr->m_map->nodes[randX][randY];

		// If target node isn't traversable, reset targetnode to nullptr to continue loop
		if (m_target->m_obstacle)
			m_target = nullptr;
	}
}

void Agent::GetRandomPos(Vec2 closestEnemyPos)
{
	m_target = nullptr;

	while (m_target == nullptr)
	{
		// Get random x pos
		int randX = rand() % (int)(m_animal.m_genes.m_detectionRange / TILE_SIZE);
		if (m_position.x < closestEnemyPos.x)
			randX *= -1;

		// Add current position to rand x pos
		randX += (int)m_currPosNode->m_position.x / TILE_SIZE;

		// Clamp x pos
		if (randX < 0)
			randX = 0;
		if (randX > m_gameMgr->m_map->gridSizeX - 1)
			randX = m_gameMgr->m_map->gridSizeX - 1;

		// Get random y pos
		int randY = rand() % (int)(m_animal.m_genes.m_detectionRange / TILE_SIZE);
		if (m_position.y < closestEnemyPos.y)
			randY *= -1;

		// Add current position to rand y pos
		randY += (int)m_currPosNode->m_position.y / TILE_SIZE;

		// Clamp y pos
		if (randY < 0)
			randY = 0;
		if (randY > m_gameMgr->m_map->gridSizeY - 1)
			randY = m_gameMgr->m_map->gridSizeY - 1;

		// Assign new target node
		m_target = &m_gameMgr->m_map->nodes[randX][randY];

		// If target node isn't traversable, reset targetnode to nullptr to continue loop
		if (m_target->m_obstacle)
			m_target = nullptr;
	}
}

// Calculates an optimal path from current position using the A* algorithm.
void Agent::CalculateAStarPath()
{
	// Reset all nodes
	for (int y = 0; y < m_gameMgr->m_map->gridSizeY; y++)
	{
		for (int x = 0; x < m_gameMgr->m_map->gridSizeX; x++)
		{
			// Reset the lot.
			m_gameMgr->m_map->nodes[x][y].m_visited = false;
			m_gameMgr->m_map->nodes[x][y].m_fScore = FLT_MAX; // Impossible number to achieve with a smaller grid.
			m_gameMgr->m_map->nodes[x][y].m_gScore = FLT_MAX; // Impossible number to achieve with a smaller grid.
			m_gameMgr->m_map->nodes[x][y].m_hScore = FLT_MAX; // Impossible number to achieve with a smaller grid.
			m_gameMgr->m_map->nodes[x][y].m_parent = nullptr;
		}
	}

	// Using this lambda for readability - to keep the longer Distance call out of the way
	// ** i.e thisNode.position.Distance(otherNode.position); **
	auto distance = [](Node* a, Node* b) { return a->m_position.Distance(b->m_position); };

	// Get start node and set its score values
	Node* current = m_startNode;
	m_startNode->m_fScore = 0;
	m_startNode->m_gScore = 0;
	m_startNode->m_hScore = distance(m_startNode, m_target);
	
	// Create list for untested nodes
	vector<Node*> untestedNodes;
	// Add starting node to list
	untestedNodes.push_back(current);
	
	// While the list isn't empty and target node hasn't been found
	while (!untestedNodes.empty() && current != m_target)
	{
		// Sort the list by hScore
		std::sort(untestedNodes.begin(), untestedNodes.end(), [](const Node* lhs, const Node* rhs) { return lhs->m_hScore < rhs->m_hScore; });
	
		// While list isn't empty and front node has been visited
		while (!untestedNodes.empty() && untestedNodes.front()->m_visited)
		{
			// Delete the first node
			untestedNodes.erase(untestedNodes.begin());
		}
	
		// Bail out of loop if list is empty
		if (untestedNodes.empty())
			break;
	
		// Set current to first node and mark as visited
		current = untestedNodes.front();
		current->m_visited = true;
	
		// For every neighbour of the current node
		for (Node* neighbour : current->m_neighbours)
		{
			// If it's node visited and is either grass or sand
			if (!neighbour->m_visited && !neighbour->m_obstacle)
			{
				// Add it to the check list
				untestedNodes.push_back(neighbour);
			}
	
			// If neighbour is perceived as closer to the target
			if (neighbour->m_gScore > current->m_gScore + distance(current, neighbour))
			{
				// Set neighbours parent
				neighbour->m_parent = current;
	
				// Calculate the nodes scores...
				neighbour->m_gScore = current->m_gScore + distance(current, neighbour);
				neighbour->m_hScore = distance(neighbour, m_target);
				neighbour->m_fScore = neighbour->m_gScore + neighbour->m_hScore;
			}
		}
	}

	// List of nodes for path
	vector<Vec2> newPath;
	// Start with target node
	Node* p = m_target;
	// At target to list
	newPath.push_back(p->m_position);
	// This was necessary 'cause animals love swimming in lakes apparently
	bool pathObtructed = false;

	// While next node isn't nullptr
	while (p->m_parent != nullptr)
	{
		// Next node isn't traversable. The path sucks.
		// Or Agent has set a target behind an obstacle that requires a longer path to get to it. The path still sucks.
		if (p->m_parent->m_obstacle)
		{
			// Fak.
			pathObtructed = true;
			break;
		}

		// Get next node and add to the path list
		p = p->m_parent;
		newPath.push_back(p->m_position);
	}

	// Path sucks or agent is trying to cheat. Bail!
	if (pathObtructed || (newPath.size() <= 1 && m_target->m_position.Distance(m_position) > TILE_SIZE))
		return;
	// Path is good. Proceed!
	else
	{
		// If agent wasn't already following a path, set a new path
		//if (path.empty())
			SetPath(newPath);
		// ...otherwise append the new path to the current path
		//else
		//	AppendToPath(newPath);
	}
}

// Seek toward the first position in the path vector then deletes it when it's there
// Rinse and repeat until the vector is empty
void Agent::Navigate()
{
	// Set current target if there is a path
	if (!m_path.empty())
		m_targetPos = { m_path.front().x, m_path.front().y };

	// Calc desired velocity
	Vec2 desiredVel = (m_targetPos - m_position);

	// Mult normalised velocity by move speed
	desiredVel = desiredVel.GetNormalised() * m_animal.m_speed;

	// Calc desired steering force
	Vec2 steeringForce = desiredVel + m_velocity;

	// Update velocity against deltaTime
	m_velocity = (m_velocity + steeringForce) * GetFrameTime();

	// Update agent position using new velocity
	m_position = (m_position + m_velocity);

	// If agent is close to the current target
	if (m_path.size() > 1)
	{
		if (m_position.Distance(m_targetPos) <= 5)
		{
			// Delete current target
			m_path.erase(m_path.begin());
		}
	}
	else if (m_path.size() == 1)
	{
		if (m_position.Distance(m_targetPos) <= 1)
		{
			// Delete current target
			m_path.erase(m_path.begin());
		}
	}
}

// Draws the agent and any debug info related to it. Noice.
void Agent::Draw()
{
	// Draw sprite
	m_animal.Draw();
}

void Agent::DrawDebug()
{
	// Draw agent detection radius
	Color viewRangeColor = YELLOW;
	viewRangeColor.a = 50;
	DrawCircle((int)m_position.x + 5, (int)m_position.y + 5, m_animal.m_genes.m_detectionRange, viewRangeColor);
	viewRangeColor.a = 255;
	DrawCircleLines((int)m_position.x + 5, (int)m_position.y + 5, m_animal.m_genes.m_detectionRange, viewRangeColor);

	// Draw path between start and end nodes
	if (!m_path.empty() && GameManager::GetInstance()->DebugActive())
	{

		DrawLine((int)m_position.x + TILE_SIZE / 2 - 10, (int)m_position.y + TILE_SIZE / 2 - 10, (int)m_path.front().x + TILE_SIZE / 2 - 10, (int)m_path.front().y + TILE_SIZE / 2 - 10, RED);
		for (size_t i = 0; i < m_path.size() - 1; i++)
		{
			DrawLine((int)m_path[i].x + TILE_SIZE / 2 - 10, (int)m_path[i].y + TILE_SIZE / 2 - 10, (int)m_path[i + 1].x + TILE_SIZE / 2 - 10, (int)m_path[i + 1].y + TILE_SIZE / 2 - 10, RED);
		}

		Color endNodeColor = RED;
		endNodeColor.a = 125;
		DrawCircle((int)m_path.back().x + 5, (int)m_path.back().y + 5, 7.5f, endNodeColor);

		if (m_animal.m_type == AnimalSelection::Sheep)
		{
			// Draw marker at closest food node
			if (m_blackboard->GetClosestFoodNode())
				DrawCircle((int)m_blackboard->GetClosestFoodNode()->m_position.x + 5, (int)m_blackboard->GetClosestFoodNode()->m_position.y + 5, 10.0f, ORANGE);
		}
		else if (m_animal.m_type == AnimalSelection::Wolf)
		{
			// Draw marker at closest food node
			if (m_blackboard->GetClosestDeadPrey())
				DrawCircle((int)m_blackboard->GetClosestDeadPrey()->m_position.x + 5, (int)m_blackboard->GetClosestDeadPrey()->m_position.y + 5, 10.0f, ORANGE);
		}

		// Draw marker at closest water node
		if (m_blackboard->GetClosestWaterNode())
			DrawCircle((int)m_blackboard->GetClosestWaterNode()->m_position.x + 5, (int)m_blackboard->GetClosestWaterNode()->m_position.y + 5, 10.0f, GREEN);
	}
}