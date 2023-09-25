#include "Window.h"

#include <iostream>

#include "GlError.h"
#include "Drawable.h"
#include "Shader.h"

bool Window::s_GLFWInit = false;
bool Window::s_GLEWInit = false;

Window::Window(const Vector2u& size, const std::string& title)
{
	create(size, title);
}

Window::Window()
{

}

Window::~Window()
{
	
}

bool Window::create(const Vector2u& size, const std::string& title)
{
	if (!s_GLFWInit)
	{
		if (!glfwInit())
		{
			std::cout << "Unable to initialize GLFW." << std::endl;
			return false;
		}

		s_GLFWInit = true;
	}

	m_GLFWWindowHandle = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
	if (!m_GLFWWindowHandle)
	{
		glfwTerminate();
		std::cout << "Couldn't open window named \"" << title << "\"." << std::endl;
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_GLFWWindowHandle);

	if (!s_GLEWInit)
	{
		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			std::cerr << "Failed to initialize GLEW" << std::endl;
			return false;
		}

		s_GLEWInit = true;
	}

	return true;
}

bool Window::isOpen() const
{
	return m_GLFWWindowHandle != nullptr;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_GLFWWindowHandle) == 0 ? false : true;
}

void Window::clear(const Color& color)
{
	GLCall(glClearColor(color.r, color.g, color.b, color.a));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::display()
{
	glfwSwapBuffers(m_GLFWWindowHandle);
}

void Window::draw(const IDrawable& drawable)
{
	drawable.draw(*this);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::setShader(const Shader& shader)
{
	GLCall(glUseProgram(shader.getID()));
}