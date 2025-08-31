#include "core/PhysicsEngine.h"
#include "core/GalaxyGenerator.h"
#include "ui/Renderer.h"
#include "ui/Camera.h"
#include <vector>
int main() {
    Cosmoverse::Renderer renderer;
    Cosmoverse::Camera camera;
    if (!renderer.initialize(1280, 720, "COSMOVERSE-ENGINE")) return -1;
    Cosmoverse::GalaxyGenerator generator;
    std::vector<Cosmoverse::Body> bodies = generator.generateSpiralGalaxy(1000, 100.0f, {0, 0, 0}, {0, 0, 0}, 1.0e29f);
    Cosmoverse::PhysicsEngine physics;
    while (!renderer.shouldClose()) {
        physics.simulate(bodies, 0.016f);
        renderer.render(bodies);
    }
    renderer.shutdown();
    return 0;
}