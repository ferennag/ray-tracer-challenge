#include <memory>
#include "engine/Window.h"
#include "raytracer/RayTracerRenderer.h"
#include "raytracer/SceneLoader.h"
#include "raytracer/ObjLoader.h"
#include "raytracer/Transformations.h"

using namespace std;

int main() {
    auto triangleGroup = ObjLoader::loadObjFile("../resources/torus.obj");
    triangleGroup->withTransformation(Transformations::scale({ 1, 2, 2 }));
    auto world = SceneLoader::loadScene("../resources/empty.yaml");
    world->addObject(std::move(triangleGroup));
    auto width = world->getCamera().getWidth();
    auto height = world->getCamera().getHeight();
    auto renderer = std::make_unique<RayTracerRenderer>(width, height);
    renderer->setClearColor({ 0, 0, 0, 1 });
    renderer->setWorld(std::move(world));

    Window window("Ray Tracer Challange", width, height, std::move(renderer));
    window.show();
    return 0;
}
