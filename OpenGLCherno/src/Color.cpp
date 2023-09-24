#include "Color.h"

const Color Color::White   = { 1.0f, 1.0f, 1.0f, 1.f };
const Color Color::Silver  = { .75f, .75f, .75f, 1.f };
const Color Color::Gray	   = { 0.5f, 0.5f, 0.5f, 1.f };
const Color Color::Black   = { 0.0f, 0.0f, 0.0f, 1.f };
const Color Color::Red	   = { 1.0f, 0.0f, 0.0f, 1.f };
const Color Color::Maroon  = { 0.5f, 0.0f, 0.0f, 1.f };
const Color Color::Yellow  = { 1.0f, 1.0f, 0.0f, 1.f };
const Color Color::Olive   = { 0.5f, 0.5f, 0.0f, 1.f };
const Color Color::Lime	   = { 0.0f, 1.0f, 0.0f, 1.f };
const Color Color::Green   = { 0.0f, 0.5f, 0.0f, 1.f };
const Color Color::Aqua	   = { 0.0f, 1.0f, 1.0f, 1.f };
const Color Color::Teal	   = { 0.0f, 0.5f, 0.5f, 1.f };
const Color Color::Blue	   = { 0.0f, 0.0f, 1.0f, 1.f };
const Color Color::Navy	   = { 0.0f, 0.0f, 0.5f, 1.f };
const Color Color::Fuchsia = { 1.0f, 0.0f, 1.0f, 1.f };
const Color Color::Purple  = { 0.5f, 0.0f, 0.5f, 1.f };

Color::Color(float r, float g, float b, float a)
	: r(r), g(g), b(b), a(a)
{

}

Color::Color(float r, float g, float b)
	: Color(r, g, b, 1.f)
{

}

Color::Color()
	: Color(0.f, 0.f, 0.f, 1.f)
{

}