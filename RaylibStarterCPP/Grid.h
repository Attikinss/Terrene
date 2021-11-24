#pragma once
#include "Node.h"
#include "GameManager.h"
#include "CustomMath.h"

/* GOOD SEEDS YO
* 123454321 - Long bois
* 908070605040302010 Messy 1.0
* 25041996 - Messy 2.0
* 05052001 - Two Islands
* 0110110111 or 439 - yeet
* 69420 - Cool
* 159753 - Ponds galore
* 112358 - Beachfront
* 9326083072033 - Legit just a barcode no#
* 1685617988 - Int converted error code
* 314159265359 - just pi
*/
#define TERRAIN_GENERATION_SEED 159753
#define TILE_SIZE 32 // Don't touch. Each tile is 32x32 pixels. Only change this to suit custom artwork size.
#define TERRAIN_SEA_LEVEL 0.25
#define TERRAIN_SAND_LEVEL 0.325
#define TERRAIN_WATER_TRANSPARENCY_BIAS 0.65 // Sweet spot
#define TERRAIN_FALLOFFMAP_MULT 3
#define TERRAIN_FALLOFFMAP_BIAS 7.5

class Grid
{
public:
	Node** nodes = nullptr;
	int gridSizeX = 0;
	int gridSizeY = 0;

	Grid() {}
	Grid(int xSize, int ySize);
	~Grid();
	void DrawTerrain();
	void DrawFoliage();
	void DrawDebug();

private:
	float** heightMap = nullptr;
	float** falloffMap = nullptr;
	float** treeMap = nullptr;
	bool useFalloff = false;
	bool generateTrees = true;
	
	void GenerateHeightMap();
	void GenerateTerrain();
	void ConnectNodes();
};