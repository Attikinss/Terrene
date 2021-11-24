#pragma once
#include "CustomMath.h"
#include <vector>

enum class NodeType
{
	Grass = 1, // Traversable
	Sand,	   // Traversable
	OakTree,
	PineTree,
	Bush,
	Cliff,
	Water,
};

struct Node
{
	NodeType m_type;
	Vec2 m_position;
	Vec2 m_texturePos;
	Node* m_parent;
	std::vector<Node*> m_neighbours;
	bool m_visited = false;
	bool m_obstacle = false;

	float m_height = 0;
	float m_fScore = 0;
	float m_gScore = 0;
	float m_hScore = 0;
};