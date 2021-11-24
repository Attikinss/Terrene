#pragma once
#include <vector>
#include "Agent.h"

typedef void(Agent::*DTAction)();
typedef bool(Agent::*DTCondition)();

class DecisionTree;

class DTNode
{
	static int m_lastID;

protected:
	const char* m_name;
	int m_id;

	Agent* m_agent = nullptr;
	DTCondition m_condition;
	DTAction m_action;

	DTNode* m_parent = nullptr;
	DTNode* m_childFail = nullptr;
	DTNode* m_childSuccess = nullptr;
	int GetID();

public:
	bool isLeafNode = false;

	DTNode(const char* name);
	void SetParent(DTNode* parent);
	DTNode* GetFailChild();
	DTNode* GetSuccessChild();

	virtual bool ConditionMet() { return m_condition; }
	virtual void ExecuteAction() {}
	virtual ~DTNode();
};

class Condition : public DTNode
{
public:
	Condition(const char* name);
	Condition(const char* name, DTCondition condition, Agent* agent, DecisionTree* tree);
	void SetCondition(DTCondition condition);
	bool ConditionMet() override; //{ return (m_agent->*m_condition)(); }
	void SetFailChild(DTNode* child);
	void SetSuccessChild(DTNode* child);
	virtual ~Condition();
};

class Leaf : public DTNode
{
public:
	Leaf(const char* name);
	Leaf(const char* name, DTAction action, Agent* agent, DecisionTree* tree);
	void SetAction(DTAction action);
	void ExecuteAction() override;
	virtual ~Leaf();
};