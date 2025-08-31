#include "GalaxyGenerator.h"
#include <glm/gtx/rotate_vector.hpp>
#include <random>
using namespace Cosmoverse;

std::vector<Body> GalaxyGenerator::generateSpiralGalaxy(int num, float radius, glm::vec3 center, glm::vec3 vel, float massSpread) {
    std::vector<Body> stars;
    std::default_random_engine rng(std::random_device{}());
    std::normal_distribution<float> massDist(1.0e30f, massSpread);
    for (int i = 0; i < num; ++i) {
        float angle = i * 0.3f;
        float dist = radius * (i / (float)num);
        glm::vec3 pos = glm::rotateY(glm::vec3(dist, 0, 0), angle) + center;
        glm::vec3 v = glm::cross(glm::vec3(0, 1, 0), pos - center);
        v = glm::normalize(v) * sqrt(6.67430e-11f * 1.0e12f / dist);
        Body b{pos, v + vel, glm::vec3(0), std::max(1.0e29f, massDist(rng))};
        stars.push_back(b);
    }
    return stars;
}