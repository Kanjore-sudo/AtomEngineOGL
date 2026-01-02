#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

class Input {
private:
    GLFWwindow* window;
public:
    Input(GLFWwindow* win) : window(win) {}
    bool IsKeyPressed(int key) { return glfwGetKey(window, key) == GLFW_PRESS; }
    bool IsMouseButtonPressed(int button) { return glfwGetMouseButton(window, button) == GLFW_PRESS; }
    void GetMousePos(double& x, double& y) { glfwGetCursorPos(window, &x, &y); }
};

#endif
