#ifndef RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
#define RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H

#include <future>
#include <glm/glm.hpp>
#include "../engine/Renderer.h"
#include "PointLight.h"
#include "Material.h"
#include "Sphere.h"
#include "World.h"

class RayTracerRenderer : public Renderer {
public:
    RayTracerRenderer(int width, int height);
    ~RayTracerRenderer() override = default;

    void render() override;
protected:
    World m_world;

    Ray rayForPixel(int x, int y) const;
    Color colorAt(const Ray &ray) const;
    [[nodiscard]] Color
    lighting(const Sphere &sphere, const PointLight &light, const glm::dvec4 &eye, const glm::dvec4 &point) const;
    [[nodiscard]] bool isShadowed(const glm::dvec4 &point, const glm::dvec4 &normal) const;
    void renderArea(int minX, int minY, int maxX, int maxY, std::promise<void> result);
};


#endif //RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
