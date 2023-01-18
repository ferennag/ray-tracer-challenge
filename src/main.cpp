#include <memory>
#include "engine/Window.h"
#include "raytracer/RayTracerRenderer.h"
#include "raytracer/SceneLoader.h"

using namespace std;

int main() {
    auto world = SceneLoader::loadScene("../resources/reflection-refraction-scene.yaml");
    auto width = world->getCamera().getWidth();
    auto height = world->getCamera().getHeight();
    auto renderer = std::make_unique<RayTracerRenderer>(width, height);
    renderer->setClearColor({0, 0, 0, 1});
    renderer->setWorld(std::move(world));

    Window window("Ray Tracer Challange", width, height, std::move(renderer));
    window.show();
    return 0;
}
