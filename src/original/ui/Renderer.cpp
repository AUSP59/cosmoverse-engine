#include "Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace Cosmoverse;
static GLFWwindow* g_window = nullptr;
bool Renderer::initialize(int width, int height, const char* title) {
    if (!glfwInit()) return false;
    g_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!g_window) return false;
    glfwMakeContextCurrent(g_window);
    if (glewInit() != GLEW_OK) return false;
    glEnable(GL_PROGRAM_POINT_SIZE);
    glClearColor(0, 0, 0.05f, 1);
    return true;
}
void Renderer::render(const std::vector<Body>& bodies) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (const auto& b : bodies) glVertex3f(b.position.x, b.position.y, b.position.z);
    glEnd();
    glfwSwapBuffers(g_window);
    glfwPollEvents();
}
void Renderer::shutdown() {
    glfwDestroyWindow(g_window);
    glfwTerminate();
}
bool Renderer::shouldClose() const {
    return glfwWindowShouldClose(g_window);
}