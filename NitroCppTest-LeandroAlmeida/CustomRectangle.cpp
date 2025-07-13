// Leandro Almeida Assessment

#include "CustomRectangle.h"
#include <iostream>

CustomRectangle::CustomRectangle(const Position2D x1, const Position2D x2, bool isToPrint)
	: LeftTopCorner(x1), RightBottomCorner(x2)
{
	UpdateWidthAndHeight();

	if (!isToPrint)
		return;

	ColoredPrintf::CPrintRectancgle(*this);
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
