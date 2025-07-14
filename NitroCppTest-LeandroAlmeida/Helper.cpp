// Leandro Almeida Assessment

#include "Helper.h"
#include "CustomRectangle.h"

void ColoredPrintf::CPrint(const string& text, const Colors& textColor)
{
	std::cout << "\033[" << textColor << "m";
	std::cout << text;
	std::cout << "\033[0m";
}

void ColoredPrintf::CPrint(const int& text, const Colors& textColor)
{
	std::cout << "\033[" << textColor << "m";
	std::cout << text;
	std::cout << "\033[0m";
}

void ColoredPrintf::CPrintRectancgle(const CustomRectangle& rect)
{
	cout << "(";
	ColoredPrintf::CPrint(rect.GetLeftTopCorner().x, ColoredPrintf::Green);
	cout << ", ";
	ColoredPrintf::CPrint(rect.GetLeftTopCorner().y, ColoredPrintf::Green);
	cout << "), w=";
	ColoredPrintf::CPrint(rect.GetWidth(), ColoredPrintf::Yellow);
	cout << ", h=";
	ColoredPrintf::CPrint(rect.GetHeight(), ColoredPrintf::Yellow);
	cout << ";\n";
}	
