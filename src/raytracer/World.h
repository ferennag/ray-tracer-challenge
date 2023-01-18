#ifndef RAY_TRACER_CHALLENGE_WORLD_H
#define RAY_TRACER_CHALLENGE_WORLD_H

#include <memory>
#include <vector>
#include "lighting/PointLight.h"
#include "shapes/Shape.h"
#include "Camera.h"

class World {
public:
    World(int width, int height);

    Intersections intersect(const Ray &ray) const;
    std::vector<PointLight> getLights() const;
    Camera getCamera() const;

    const std::vector<std::unique_ptr<Shape>> &getObjects() const { return m_objects; }

    void addObject(std::unique_ptr<Shape> object) { m_objects.push_back(std::move(object)); }

    static std::unique_ptr<World> defaultWorld(int width = 1000, int height = 1000);

private:
    std::vector<std::unique_ptr<Shape>> m_objects;
    std::vector<PointLight> m_lights;
    Camera m_camera;
};

#endif //RAY_TRACER_CHALLENGE_WORLD_H
