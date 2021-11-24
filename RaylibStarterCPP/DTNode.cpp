#include "DTNode.h"
#include "DecisionTree.h"

int DTNode::m_lastID = 0;

DTNode::DTNode(const char* name) : m_name(name), m_id(++m_lastID) {}

int DTNode::GetID()
{
	return m_id;
}

void DTNode::SetParent(DTNode* parent)
{
	this->m_parent = parent;
}

DTNode* DTNode::GetFailChild()
{
	if (m_childFail != nullptr)
		return m_childFail;

	return nullptr;
}

DTNode* DTNode::GetSuccessChild()
{
	if (m_childSuccess != nullptr)
		return m_childSuccess;

	return nullptr;
}

DTNode::~DTNode()
{
}
