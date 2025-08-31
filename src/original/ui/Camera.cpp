#include "Camera.h"
using namespace Cosmoverse;
Camera::Camera() : position(0.0f, 0.0f, 300.0f) {}
glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, glm::vec3(0,0,0), glm::vec3(0,1,0));
}