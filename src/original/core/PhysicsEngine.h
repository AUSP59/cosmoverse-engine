#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H
#include <vector>
#include <glm/glm.hpp>
namespace Cosmoverse {
    struct Body {
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 force;
        float mass;
    };
    class PhysicsEngine {
    public:
        void simulate(std::vector<Body>& bodies, float deltaTime);
    };
}
#endif