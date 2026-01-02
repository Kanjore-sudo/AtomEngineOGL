#include "AtomEngine.hpp"

using namespace AtomEngine;

Window::Window(const std::string& title, int w, int h) : width(w), height(h)
{
    if (!glfwInit()) {
        std::cerr << "Error inicializando GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Error creando ventana GLFW" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error inicializando GLEW" << std::endl;
        return;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window()
{
    if (window) glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::Create() { return window != nullptr; }

void Window::Show() { glfwShowWindow(window); }

int Window::Run(GameObject* scene)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        scene->Process(this);

        glfwSwapBuffers(window);
    }
    return 0;
}
