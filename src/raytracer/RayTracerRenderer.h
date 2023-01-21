#ifndef RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
#define RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H

#include <random>
#include <future>
#include <glm.hpp>
#include "../engine/Renderer.h"
#include "lighting/PointLight.h"
#include "lighting/Material.h"
#include "shapes/Sphere.h"
#include "World.h"
#include "Computations.h"

class RayTracerRenderer : public Renderer {
public:
    RayTracerRenderer(int width, int height);
    ~RayTracerRenderer() override = default;

    void render() override;

    [[nodiscard]] Color lighting(const PointLight &light, const Computations &comps) const;

    [[nodiscard]] bool isShadowed(const glm::dvec4 &point) const;

    [[nodiscard]] Color reflectedColor(const Computations &comps, int remaining) const;

    [[nodiscard]] Color refractedColor(const Computations &comps, int remaining) const;

    [[nodiscard]] const World &getWorld() const { return *m_world; }

    void setWorld(std::unique_ptr<World> world) { m_world = std::move(world); }

protected:
    const int reflectionDepthLimit = 3;
    const int samples = 0;
    std::mt19937_64 m_randEngine;
    std::unique_ptr<World> m_world;

    Ray rayForPixel(double x, double y) const;
    Color colorAt(const Ray &ray, int remaining) const;

    void renderArea(int minX, int minY, int maxX, int maxY, std::promise<void> result);
};


#endif //RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
