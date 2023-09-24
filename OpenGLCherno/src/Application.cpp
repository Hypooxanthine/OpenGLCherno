#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Window.h"
#include "Vector.h"
#include "Mesh.h"
#include "Shader.h"

int main(void)
{
    Window win({ 640, 640 }, "Hello World");

    if (!win.isOpen())
    {
        std::cout << "Couldn't open window." << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    Mesh m;
    m.loadFromFile("Meshes/test.mesh");

    /*Vertex v;
    v.position = {-1.f, -1.f, 0.f};
    v.normal = { -1.f, -1.f, 0.f }; 
    m.addVertex(v);
    v.position = { 1.f, -1.f, 0.f };
    v.normal = { 1.f, -1.f, 0.f };
    m.addVertex(v);
    v.position = { 0.f, 1.f, 0.f };
    v.normal = { 0.f, 1.f, 0.f };
    m.addVertex(v);

    m.defineTriangle(0, 1, 2);*/

    Shader shader;
    if (!shader.loadFromFile("Shaders/vertex.shader", "Shaders/fragment.shader"))
    {
        std::cout << "Error while loading shaders." << std::endl;
        return -1;
    }

    glUseProgram(shader.getID());

    /* Loop until the user closes the window */
    while (!win.shouldClose())
    {
        win.pollEvents();

        win.clear();

        win.draw(m);

        win.display();
    }

    glfwTerminate();
    return 0;
}