// Leandro Almeida Assessment

#include "CustomRectangle.h"
#include <iostream>

CustomRectangle::CustomRectangle(Position2D x1, Position2D x2)
	: LeftTopCorner(x1), RightBottomCorner(x2)
{
	UpdateWidthAndHeight();

	printf("Rectangle created on position (%.2f, %.2f) ", LeftTopCorner.x, LeftTopCorner.y);
	printf("with the size (%.2f, %.2f)\n", width, height);
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
