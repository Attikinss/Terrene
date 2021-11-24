#include "BoundingBox.h"

bool BBox::PosInBounds(Vec2 pos)
{
	return (pos.x >= topleft.x && pos.y >= topleft.y && pos.x <= bottomRight.x && pos.y <= bottomRight.y);
}
