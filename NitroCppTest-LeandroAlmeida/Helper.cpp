
#include "Helper.h"

void ColoredPrintf::CPrint(const string& text, Colors textColor)
{
	std::cout << "\033[" << textColor << "m";
	std::cout << text;
	std::cout << "\033[0m";
}
