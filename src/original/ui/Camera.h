#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Cosmoverse {
    class Camera {
    public:
        Camera();
        glm::mat4 getViewMatrix() const;
    private:
        glm::vec3 position;
    };
}
#endif