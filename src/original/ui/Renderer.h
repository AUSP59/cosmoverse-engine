#ifndef RENDERER_H
#define RENDERER_H
#include "../core/PhysicsEngine.h"
#include <vector>
namespace Cosmoverse {
    class Renderer {
    public:
        bool initialize(int width, int height, const char* title);
        void render(const std::vector<Body>& bodies);
        void shutdown();
        bool shouldClose() const;
    };
}
#endif