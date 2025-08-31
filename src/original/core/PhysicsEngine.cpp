#include "PhysicsEngine.h"
using namespace Cosmoverse;

void PhysicsEngine::simulate(std::vector<Body>& bodies, float deltaTime) {
    const float G = 6.67430e-11f;
    for (auto& body : bodies) body.force = glm::vec3(0.0f);
    for (size_t i = 0; i < bodies.size(); ++i) {
        for (size_t j = i + 1; j < bodies.size(); ++j) {
            glm::vec3 dir = bodies[j].position - bodies[i].position;
            float distSqr = glm::dot(dir, dir) + 1e-5f;
            glm::vec3 force = glm::normalize(dir) * (G * bodies[i].mass * bodies[j].mass / distSqr);
            bodies[i].force += force;
            bodies[j].force -= force;
        }
    }
    for (auto& body : bodies) {
        glm::vec3 acc = body.force / body.mass;
        body.velocity += acc * deltaTime;
        body.position += body.velocity * deltaTime;
    }
}