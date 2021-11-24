#include "Grid.h"
#include <sstream>

Grid::Grid(int xSize, int ySize)
{
	// Assign a map size
	gridSizeX = xSize;
	gridSizeY = ySize;

	// Create nodes, heightmap and treemap
	nodes = new Node*[gridSizeX];
	heightMap = new float*[gridSizeX];
	treeMap = new float*[gridSizeX];
	for (int i = 0; i < gridSizeX; i++)
	{
		nodes[i] = new Node[gridSizeY];
		heightMap[i] = new float[gridSizeY];
		treeMap[i] = new float[gridSizeY];
	}

	// If using it, create the falloffmap
	if (useFalloff)
	{
		falloffMap = new float*[gridSizeX];
		for (int i = 0; i < gridSizeX; i++)
			falloffMap[i] = new float[gridSizeY];
	}

	GenerateHeightMap();
	GenerateTerrain();
}

Grid::~Grid()
{
	// Delete all nodes
	for (int i = 0; i < gridSizeX; i++)
		delete[] nodes[i];
	
	delete[] nodes;
}

void Grid::GenerateHeightMap()
{
	PerlinNoise(heightMap, gridSizeX, gridSizeY, 0.9f / 1.85f, TERRAIN_GENERATION_SEED, 2, 0.5f, 1.87f);

	if (generateTrees)
		PerlinNoise(treeMap, gridSizeX, gridSizeY, 0.175f / 1.85f, TERRAIN_GENERATION_SEED, 2, 1.0f, 2.0f);

	if (useFalloff)
		Falloff(falloffMap, gridSizeX, gridSizeY, (float)TERRAIN_FALLOFFMAP_BIAS);
}

void Grid::GenerateTerrain()
{
	int borderBias = 2;

	for (int y = 0; y < gridSizeY; y++)
	{
		for (int x = 0; x < gridSizeX; x++)
		{
			nodes[x][y].m_position = { (float)x * TILE_SIZE + 10, (float)y * TILE_SIZE + 10 };
			nodes[x][y].m_parent = nullptr;	

			// Use falloffmap
			if (useFalloff)
			{
				nodes[x][y].m_height = Clamp(heightMap[x][y] - falloffMap[x][y], 0.0f, 1.0f);
				int i = 0;
			}
			else
				nodes[x][y].m_height = heightMap[x][y];

			// Is the node grass, sand or water?
			NodeType temp;
			bool isObstacle = false;
			Vec2 texPos = { 0, 0 };

			if (nodes[x][y].m_height <= TERRAIN_SEA_LEVEL)
			{
				temp = NodeType::Water;
				isObstacle = true;
			}
			else if (nodes[x][y].m_height > TERRAIN_SEA_LEVEL && nodes[x][y].m_height <= TERRAIN_SAND_LEVEL)
				temp = NodeType::Sand;
			else
				temp = NodeType::Grass;

			// ...or is it a tree?
			if (treeMap[x][y] > TERRAIN_SAND_LEVEL && treeMap[x][y] < 0.5f && temp == NodeType::Grass)
			{
				float offsetX = RandomFloat(-7.5, 7.5);
				float offsetY = RandomFloat(-7.5, 7.5);
				texPos = { offsetX, offsetY };

				if (treeMap[x][y] < 0.4f)
				{
					temp = NodeType::Bush;
					texPos /= 3;
					isObstacle = false;
				}
				else
				{
					temp = NodeType::PineTree;
					isObstacle = true;
				}
			}

			nodes[x][y].m_type = temp;
			nodes[x][y].m_obstacle = isObstacle;
			nodes[x][y].m_texturePos = nodes[x][y].m_position + texPos;
		}
	}

	ConnectNodes();
}

void Grid::ConnectNodes()
{
	for (int y = 0; y < gridSizeY; y++)
	{
		for (int x = 0; x < gridSizeX; x++)
		{
			// Horiztonal and vertical connections
			if (x > 0)
				nodes[x][y].m_neighbours.push_back(&nodes[x - 1][y]);
			if (x < gridSizeX - 1)
				nodes[x][y].m_neighbours.push_back(&nodes[x + 1][y]);
			if (y > 0)
				nodes[x][y].m_neighbours.push_back(&nodes[x][y - 1]);
			if (y < gridSizeY - 1)
				nodes[x][y].m_neighbours.push_back(&nodes[x][y + 1]);

			// Diagonal connections
			if (x > 0 && y > 0)
				nodes[x][y].m_neighbours.push_back(&nodes[x - 1][y - 1]);
			if (x < gridSizeX - 1 && y > 0)
				nodes[x][y].m_neighbours.push_back(&nodes[x + 1][y - 1]);
			if (x > 0 && y < gridSizeY - 1)
				nodes[x][y].m_neighbours.push_back(&nodes[x - 1][y + 1]);
			if (x < gridSizeX - 1 && y < gridSizeY - 1)
				nodes[x][y].m_neighbours.push_back(&nodes[x + 1][y + 1]);

			/*Node* highest = nullptr;
			Node* lowest = nullptr;
			for (Node* neighbour : nodes[x][y].neighbours)
			{
				if (highest == nullptr || neighbour->height > highest->height)
					highest = neighbour;
				if (lowest == nullptr || neighbour->height < lowest->height)
					lowest = neighbour;
			}
			if (lowest && highest)
			{
				if (highest->height - lowest->height >= 0.2f)
				{
					float offsetX = RandomFloat(-5, 5);
					float offsetY = RandomFloat(-5, 5);
					nodes[x][y].texturePos += Vec2(offsetX, offsetY);
					nodes[x][y].type = NodeType::Cliff;
					nodes[x][y].obstacle = true;
				}
			}*/
		}
	}
}

void Grid::DrawTerrain()
{
	for (int y = 0; y < gridSizeY; y++)
	{
		for (int x = 0; x < gridSizeX; x++)
		{
			Texture tex;
			Color color = WHITE;
			float minAlpha = 0;
			float maxAlpha = 0;
			float targetAlpha = 0;
			float alphaPercentage = 0;

			switch (nodes[x][y].m_type)
			{
				case NodeType::Water:
				{
					// Setup sand values
					alphaPercentage = nodes[x][y].m_height / (float)TERRAIN_SEA_LEVEL;
					targetAlpha = alphaPercentage * 255;
					minAlpha = 20;
					maxAlpha = 170;

					if (targetAlpha < minAlpha)
						color.a = (unsigned char)minAlpha;

					// Draw sand below water
					color.a = (unsigned char)targetAlpha;
					tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("Sand");
					DrawTexture(tex, (int)(nodes[x][y].m_position.x - tex.width / (TILE_SIZE / 10)), (int)(nodes[x][y].m_position.y - tex.height / (TILE_SIZE / 10)), color);

					// Setup water values
					targetAlpha *= (float)-TERRAIN_WATER_TRANSPARENCY_BIAS;
					if (targetAlpha < minAlpha || targetAlpha > maxAlpha)
						targetAlpha = maxAlpha;

					// Draw water
					color.a = (unsigned char)targetAlpha;
					tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("Water");
					DrawTexture(tex, (int)(nodes[x][y].m_position.x - tex.width / (TILE_SIZE / 10)), (int)(nodes[x][y].m_position.y - tex.height / (TILE_SIZE / 10)), color);
					break;
				}

				case NodeType::Sand:
				{
					alphaPercentage = (nodes[x][y].m_height / (float)TERRAIN_SAND_LEVEL);
					targetAlpha = alphaPercentage * 255;
					minAlpha = 200;
					maxAlpha = 255;

					if (targetAlpha < minAlpha)
						targetAlpha = minAlpha;
					if (targetAlpha > maxAlpha)
						targetAlpha = maxAlpha;

					color.a = (unsigned char)targetAlpha;

					tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("Sand");
					DrawTexture(tex, (int)(nodes[x][y].m_position.x - tex.width / (TILE_SIZE / 10)), (int)(nodes[x][y].m_position.y - tex.height / (TILE_SIZE / 10)), color);
					break;
				}

				case NodeType::Grass:
				case NodeType::OakTree:
				case NodeType::PineTree:
				case NodeType::Bush:
				{
					alphaPercentage = nodes[x][y].m_height + (float)TERRAIN_SAND_LEVEL;
					targetAlpha = alphaPercentage * 255;
					minAlpha = 200;
					maxAlpha = 255;

					if (targetAlpha < minAlpha)
						targetAlpha = minAlpha;
					if (targetAlpha > maxAlpha)
						targetAlpha = maxAlpha;

					color.a = (unsigned char)targetAlpha;

					tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("Grass");
					DrawTexture(tex, (int)(nodes[x][y].m_position.x - tex.width / (TILE_SIZE / 10)), (int)(nodes[x][y].m_position.y - tex.height / (TILE_SIZE / 10)), color);
					break;
				}

				default:
					break;
			}
		}
	}
}

void Grid::DrawFoliage()
{
	for (int y = 0; y < gridSizeY; y++)
	{
		for (int x = 0; x < gridSizeX; x++)
		{
			Texture tex;
			Color color = WHITE;
			if (nodes[x][y].m_type == NodeType::PineTree)
			{
				Vec2 nodeOffset = { 0, (float)TILE_SIZE / 3 };
				float distToMousePos = nodes[x][y].m_position.Distance(GameManager::GetInstance()->MousePosition() + nodeOffset);
				if (distToMousePos <= TILE_SIZE * 3)
				{
					float alphaPercentage = 255 * (distToMousePos / (float)TILE_SIZE * 0.35f);
					alphaPercentage = Clamp(alphaPercentage, 92.0f, 255.0f);
					color.a = (unsigned char)alphaPercentage;
				}

				tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("PineTree");
				DrawTexture(tex, (int)(nodes[x][y].m_texturePos.x - tex.width / (TILE_SIZE / 10)), (int)nodes[x][y].m_texturePos.y - tex.height + 10, color);
			}
			else if (nodes[x][y].m_type == NodeType::OakTree)
			{
				tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("OakTree");
				DrawTexture(tex, (int)(nodes[x][y].m_texturePos.x - tex.width / (TILE_SIZE / 10) - 2), (int)nodes[x][y].m_texturePos.y - tex.height + 15, color);
			}
			else if (nodes[x][y].m_type == NodeType::Bush)
			{
				tex = GameManager::GetInstance()->textureMgr->GetTerrainSprite("Fern");
				DrawTexture(tex, (int)(nodes[x][y].m_texturePos.x - tex.width / 3.2f), (int)(nodes[x][y].m_texturePos.y - tex.height / 2.0f), color);
			}
		}
	}
}

void Grid::DrawDebug()
{
	for (int y = 0; y < gridSizeY; y++)
	{
		for (int x = 0; x < gridSizeX; x++)
		{
			if (!nodes[x][y].m_obstacle)
			{
				Color color = { 130, 255, 225, 220 };
				for (Node* neighbour : nodes[x][y].m_neighbours)
				{
					// Only draw lines to the following neighbours [ Upper Right - Right - Lower Right - Lower]
					if (neighbour->m_position.x > nodes[x][y].m_position.x || (neighbour->m_position.x == nodes[x][y].m_position.x && neighbour->m_position.y > nodes[x][y].m_position.y))
					{
						// Only draw lines to neighbours that are traversable
						if (!neighbour->m_obstacle)
							DrawLine((int)nodes[x][y].m_position.x + TILE_SIZE / 2 - 10, (int)nodes[x][y].m_position.y + TILE_SIZE / 2 - 10,
									(int)neighbour->m_position.x + TILE_SIZE / 2 - 10, (int)neighbour->m_position.y + TILE_SIZE / 2 - 10, color);
					}
				}
			}
		}
	}
}