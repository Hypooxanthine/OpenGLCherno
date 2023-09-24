#pragma once

class Color
{
public:
	Color(float r, float g, float b, float a);
	Color(float r, float g, float b);
	Color();

public:
	float r, g, b, a;

public:
	static const Color White;
	static const Color Silver;
	static const Color Gray;
	static const Color Black;
	static const Color Red;
	static const Color Maroon;
	static const Color Yellow;
	static const Color Olive;
	static const Color Lime;
	static const Color Green;
	static const Color Aqua;
	static const Color Teal;
	static const Color Blue;
	static const Color Navy;
	static const Color Fuchsia;
	static const Color Purple;
};