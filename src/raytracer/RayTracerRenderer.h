#ifndef RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
#define RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H

#include <future>
#include <glm/glm.hpp>
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
    [[nodiscard]] Color reflectedColor(const Computations &comps, int remaining) const;
protected:
    const int reflectionDepthLimit = 3;
    World m_world;

    Ray rayForPixel(int x, int y) const;
    Color colorAt(const Ray &ray, int remaining) const;

    [[nodiscard]] Color lighting(const PointLight &light, const Computations &comps) const;

    [[nodiscard]] Color refractedColor(const Computations &comps, int remaining) const;

    [[nodiscard]] bool isShadowed(const glm::dvec4 &point) const;

    void renderArea(int minX, int minY, int maxX, int maxY, std::promise<void> result);
};


#endif //RAY_TRACER_CHALLENGE_RAYTRACERRENDERER_H
