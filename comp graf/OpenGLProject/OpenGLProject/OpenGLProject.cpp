#include <iostream>

#include "glad.h"
#include "glfw3.h"

int main()
{
    GLFWwindow* window = nullptr;

    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    window = glfwCreateWindow(1600, 900, "Test window!", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);
    glfwSwapInterval(1);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0f, -1.0f, 0.0f);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(1.0f, -1.0f, 0.0f);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0f, 1.0f, 0.0f);

        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
