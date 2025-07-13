// Leandro Almeida Assessment

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Position2D
{
public:
	int x;
	int y;

	Position2D(int _x, int _y) : x(_x), y(_y) {}
};

class ColoredPrintf
{
public:
	enum Colors
	{
		Red = 31,
		Green = 32,
		Cyan = 36,
		Yellow = 33
	};

	/// <summary>
	/// Print a string
	/// </summary>
	/// <param name="text">text value</param>
	/// <param name="textColor">Color e.g. ColoredPrintf.Cyan</param>
	static void CPrint(const string& text, const Colors& textColor);
	
	/// <summary>
	/// Print an int
	/// </summary>
	/// <param name="text">int value</param>
	/// <param name="textColor">Color e.g. ColoredPrintf.Cyan</param>
	static void CPrint(const int& text, const Colors& textColor);

	static void CPrintRectancgle(const class CustomRectangle& rect);
};
