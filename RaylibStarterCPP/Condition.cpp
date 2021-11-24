#include "DTNode.h"
#include "Agent.h"
#include "DecisionTree.h"
#include <iostream>

Condition::Condition(const char* name) : DTNode(name)
{
	m_name = name;
}

Condition::Condition(const char* name, DTCondition condition, Agent* agent, DecisionTree* tree) : DTNode(name)
{
	m_name = name;
	m_condition = condition;
	m_agent = agent;

	if (tree != nullptr)
		tree->AddToList(this);
}

void Condition::SetCondition(DTCondition condition)
{
	m_condition = condition;
}

bool Condition::ConditionMet()
{
	return (m_agent->*m_condition)();
}

void Condition::SetFailChild(DTNode* child)
{
	m_childFail = child;
	child->SetParent(this);
}

void Condition::SetSuccessChild(DTNode* child)
{
	m_childSuccess = child;
	child->SetParent(this);
}

Condition::~Condition()
{
}
