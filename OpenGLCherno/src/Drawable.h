#pragma once

#include "Window.h"

class IDrawable
{
public:
	virtual void draw(Window& window) const = 0;
};