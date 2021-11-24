#include "DTNode.h"
#include "Agent.h"
#include "DecisionTree.h"

Leaf::Leaf(const char* name) : DTNode(name)
{
	m_name = name;
	isLeafNode = true;
}

Leaf::Leaf(const char* name, DTAction action, Agent* agent, DecisionTree* tree) : DTNode(name)
{
	m_name = name;
	m_action = action;
	isLeafNode = true;
	m_agent = agent;
	
	if (tree != nullptr)
		tree->AddToList(this);
}

void Leaf::SetAction(DTAction action)
{
	m_action = action;
}

void Leaf::ExecuteAction()
{
	(m_agent->*m_action)();
}

Leaf::~Leaf()
{
}
