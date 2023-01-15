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
    Ray rayForPixel(int x, int y) const;
    World &getWorld();
protected:
    World m_world;

    [[nodiscard]] Color lighting(const Sphere &sphere, const PointLight &light, const glm::vec4 &eye, const glm::vec4 &point) const;
    [[nodiscard]] bool isShadowed(const glm::vec4 &point, const glm::vec4 &normal) const;
    Color colorAt(const Ray &ray) const;
};


#endif //RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
