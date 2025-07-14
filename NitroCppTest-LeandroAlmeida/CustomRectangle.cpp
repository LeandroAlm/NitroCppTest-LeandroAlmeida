// Leandro Almeida Assessment

#include "CustomRectangle.h"
#include <iostream>

bool CustomRectangle::Verify() const
{
	if (width <= 0 || height <= 0)
		return false;

	return true;
}
