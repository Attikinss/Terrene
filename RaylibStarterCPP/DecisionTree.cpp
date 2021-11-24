#include "DecisionTree.h"
#include "DTNode.h"

DecisionTree::DecisionTree()
{

}

DecisionTree::~DecisionTree()
{
	for (DTNode* node : m_allNodes)
	{
		if (node->GetFailChild() != nullptr)
			node->GetFailChild()->SetParent(nullptr);

		if (node->GetSuccessChild() != nullptr)
			node->GetSuccessChild()->SetParent(nullptr);

		delete node;
		node = nullptr;
	}
}

void DecisionTree::Traverse()
{
	// Bail if root doesn't exist
	if (m_root == nullptr)
		return;

	m_currNode = m_root;
	while (!m_currNode->isLeafNode)
	{
		if (m_currNode->ConditionMet())
			m_currNode = m_currNode->GetSuccessChild();
		else
			m_currNode = m_currNode->GetFailChild();
	}

	m_currNode->ExecuteAction();
	m_currNode = nullptr;
}

void DecisionTree::SetRoot(DTNode* node)
{
	if (m_root != nullptr)
		return;

	m_root = node;
}
