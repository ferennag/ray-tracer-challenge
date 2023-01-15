#ifndef RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
#define RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H

#include <glm/glm.hpp>
#include "engine/Renderer.h"
#include "raytracer/PointLight.h"
#include "raytracer/Material.h"
#include "raytracer/Sphere.h"
#include "raytracer/World.h"

class RayTracerRenderer: public Renderer{
public:
    RayTracerRenderer(int width, int height);
    ~RayTracerRenderer() override = default;

    void render() override;
protected:
    World m_world;
    glm::vec4 m_eye;

    [[nodiscard]] Color lighting(const Sphere &sphere, const PointLight &light, const glm::vec4 &point) const;
};


#endif //RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
