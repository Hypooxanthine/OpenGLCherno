#pragma once

#include <string>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "Vector.h"
#include "Color.h"

class IDrawable;
class Shader;

class Window
{
public:
	Window(const Vector2u& size, const std::string& title);
	Window();

	virtual ~Window();

	bool create(const Vector2u& size, const std::string& title);

	bool isOpen() const;
	bool shouldClose() const;

	void clear(const Color& color = Color::Black);
	void display();

	void draw(const IDrawable& drawable);

	void pollEvents();

	void setShader(const Shader& shader);

private:
	static bool s_GLFWInit;
	static bool s_GLEWInit;

	GLFWwindow* m_GLFWWindowHandle = nullptr;
};