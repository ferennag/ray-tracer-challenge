#ifndef RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
#define RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H

#include <future>
#include <glm/glm.hpp>
#include "../engine/Renderer.h"
#include "lighting/PointLight.h"
#include "lighting/Material.h"
#include "shapes/Sphere.h"
#include "World.h"

class RayTracerRenderer : public Renderer {
public:
    RayTracerRenderer(int width, int height);
    ~RayTracerRenderer() override = default;

    void render() override;
protected:
    const int reflectionDepthLimit = 10;
    World m_world;

    Ray rayForPixel(int x, int y) const;
    Color colorAt(const Ray &ray, const int remaining) const;
    [[nodiscard]] Color
    lighting(const Shape &shape, const PointLight &light, const glm::dvec4 &eye, const glm::dvec4 &point) const;
    [[nodiscard]] Color reflectedColor(const Shape &shape, const Ray &ray, const glm::dvec4 &point, const int remaining) const;
    [[nodiscard]] bool isShadowed(const glm::dvec4 &point, const glm::dvec4 &normal) const;
    void renderArea(int minX, int minY, int maxX, int maxY, std::promise<void> result);
};


#endif //RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
