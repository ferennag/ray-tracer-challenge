#include <memory>
#include "engine/Window.h"
#include "raytracer/RayTracerRenderer.h"

using namespace std;

int main() {
    const int width { 1000 }, height { 1000 };
    auto renderer = std::make_unique<RayTracerRenderer>(width, height);
    renderer->setClearColor({0, 0, 0, 1});

    Window window("Ray Tracer Challange", width, height, std::move(renderer));
    window.show();
    return 0;
}
