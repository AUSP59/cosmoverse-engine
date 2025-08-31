#ifndef GALAXY_GENERATOR_H
#define GALAXY_GENERATOR_H
#include "PhysicsEngine.h"
#include <vector>
namespace Cosmoverse {
    class GalaxyGenerator {
    public:
        std::vector<Body> generateSpiralGalaxy(int numStars, float radius, glm::vec3 center, glm::vec3 velocity, float massSpread);
    };
}
#endif