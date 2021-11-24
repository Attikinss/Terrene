#pragma once
#include <vector>

class DTNode;

class DecisionTree
{
private:
	DTNode* m_root = nullptr;
	DTNode* m_currNode = nullptr;

	std::vector<DTNode*> m_allNodes;

public:
	DecisionTree();
	~DecisionTree();
	void Traverse();
	void SetRoot(DTNode* node);
	void AddToList(DTNode* node) { m_allNodes.push_back(node); }
};