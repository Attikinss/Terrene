#pragma once
#include "CustomMath.h"

struct BBox
{
	Vec2 topleft;
	Vec2 bottomRight;

	bool PosInBounds(Vec2 pos);
};