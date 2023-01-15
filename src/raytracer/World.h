#ifndef RAY_TRACER_CHALLENGE_WORLD_H
#define RAY_TRACER_CHALLENGE_WORLD_H

#include <vector>
#include "PointLight.h"
#include "Sphere.h"

class World {
public:
    World();

    Intersections intersect(const Ray &ray);
    std::vector<PointLight> getLights() const;
private:
    std::vector<Sphere> m_objects;
    std::vector<PointLight> m_lights;
};


#endif //RAY_TRACER_CHALLENGE_WORLD_H
