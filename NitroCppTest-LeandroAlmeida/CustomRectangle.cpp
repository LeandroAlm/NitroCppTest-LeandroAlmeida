// Leandro Almeida Assessment

#include "CustomRectangle.h"
#include <iostream>

CustomRectangle::CustomRectangle(const Position2D x1, const Position2D x2, bool isToPrint)
	: LeftTopCorner(x1), RightBottomCorner(x2)
{
	UpdateWidthAndHeight();

	if (!isToPrint)
		return;

	printf("(%.2f, %.2f), w=%.2f, h=%.2f;\n", LeftTopCorner.x, LeftTopCorner.y, width, height);
}

bool CustomRectangle::Verify() const
{
	if (LeftTopCorner.x > RightBottomCorner.x || LeftTopCorner.y > RightBottomCorner.y)
		return false;

	return true;
}

void CustomRectangle::UpdateWidthAndHeight()
{
	width = RightBottomCorner.x - LeftTopCorner.x;
	height = RightBottomCorner.y - LeftTopCorner.y;
}
