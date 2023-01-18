#ifndef RAY_TRACER_CHALLENGE_WORLD_H
#define RAY_TRACER_CHALLENGE_WORLD_H

#include <memory>
#include <vector>
#include <string_view>
#include "lighting/PointLight.h"
#include "shapes/Shape.h"
#include "Camera.h"

class World {
public:
    World() = default;

    Intersections intersect(const Ray &ray) const;
    std::vector<PointLight> getLights() const;
    Camera getCamera() const;

    const std::vector<std::unique_ptr<Shape>> &getObjects() const { return m_objects; }

    void addObject(std::unique_ptr<Shape> object) { m_objects.push_back(std::move(object)); }

    void addLight(const PointLight &light) { m_lights.push_back(light); }

    void setCamera(const Camera &camera) { m_camera = camera; }

private:
    std::vector<std::unique_ptr<Shape>> m_objects;
    std::vector<PointLight> m_lights;
    Camera m_camera;
};

#endif //RAY_TRACER_CHALLENGE_WORLD_H
