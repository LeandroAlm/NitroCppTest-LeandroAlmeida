// Leandro Almeida Assessment

#pragma once

#include "Helper.h"

class CustomRectangle
{
private:
	class Position2D LeftTopCorner;
	Position2D RightBottomCorner;
	double width = 0;
	double height = 0;

public:
	CustomRectangle(Position2D x1, Position2D x2);
	bool Verify() const;

	void UpdateWidthAndHeight();

	Position2D GetLeftTopCorner() const { return LeftTopCorner; };
	Position2D GetRightBottomCorner() const { return RightBottomCorner; };

};

