#ifndef RAY_TRACER_CHALLENGE_WORLD_H
#define RAY_TRACER_CHALLENGE_WORLD_H

#include <vector>
#include "PointLight.h"
#include "Sphere.h"
#include "Camera.h"

class World {
public:
    World(int width, int height);

    Intersections intersect(const Ray &ray) const;
    std::vector<PointLight> getLights() const;
    Camera getCamera() const;
private:
    std::vector<Sphere> m_objects;
    std::vector<PointLight> m_lights;
    Camera m_camera;
};

#endif //RAY_TRACER_CHALLENGE_WORLD_H
