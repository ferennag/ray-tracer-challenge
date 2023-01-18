#include <memory>
#include "engine/Window.h"
#include "raytracer/RayTracerRenderer.h"
#include "raytracer/SceneParser.h"

using namespace std;

int main() {
    SceneParser parser;
    auto world = parser.loadScene("../resources/test-scene.yaml");
    auto width = world->getCamera().getWidth();
    auto height = world->getCamera().getHeight();
    auto renderer = std::make_unique<RayTracerRenderer>(width, height);
    renderer->setClearColor({0, 0, 0, 1});
    renderer->setWorld(std::move(world));

    Window window("Ray Tracer Challange", width, height, std::move(renderer));
    window.show();
    return 0;
}
