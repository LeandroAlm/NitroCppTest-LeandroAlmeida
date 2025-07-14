// Leandro Almeida Assessment

#pragma once

#include "Helper.h"

class CustomRectangle
{
private:
	class Position2D LeftTopCorner;
	int width = 0;
	int height = 0;

public:
	CustomRectangle(const Position2D x1, const int _width, const int _height, bool isToPrint = false) :
		LeftTopCorner(x1), width(_width), height(_height) {};
	bool Verify() const;

	Position2D GetLeftTopCorner() const { return LeftTopCorner; };
	int GetWidth() const { return width; };
	int GetHeight() const { return height; };

};
