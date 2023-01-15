#include <glm/gtc/matrix_transform.hpp>
#include "RayTracerRenderer.h"
#include "raytracer/Ray.h"
#include "raytracer/RayMath.h"
#include "raytracer/Sphere.h"

RayTracerRenderer::RayTracerRenderer(int width, int height) : Renderer(width, height), m_world(width, height) {
}

void RayTracerRenderer::render() {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            auto ray = rayForPixel(x, y);
            auto color = colorAt(ray);
            m_buffer[y][x].copy(color);
        }
    }
}

Color RayTracerRenderer::colorAt(const Ray &ray) const {
    auto eye = -ray.getDirection();
    auto intersections = m_world.intersect(ray);
    auto hit = intersections.hit();

    if (hit.has_value()) {
        auto intersection = hit.value();
        auto point = ray.at(intersection.distance);
        Color finalColor { 0, 0, 0, 1 };
        for (auto &light: m_world.getLights()) {
            finalColor += lighting(*intersection.object, light, eye, point);
        }
        return finalColor;
    } else {
        return { 0, 0, 0, 1 };
    }
}


Color RayTracerRenderer::lighting(const Sphere &sphere, const PointLight &light, const glm::dvec4 &eye,
                                  const glm::dvec4 &point) const {
    auto material = sphere.getMaterial();
    auto normal = sphere.getNormalAt(point);
    // TODO removing acne. But the 100 multiplier should not be necessary
    auto overPoint = point + normal * PRECISION;
    if (isShadowed(overPoint, normal)) {
        return { 0.1, 0.1, 0.1, 1.0 };
    }

    auto effectiveColor = material.color * light.getIntensity();
    auto lightDir = glm::normalize(light.getPosition() - overPoint);
    auto ambient = effectiveColor * material.ambient;
    auto lightNormalAngle = glm::dot(lightDir, normal);

    if (lightNormalAngle < 0) {
        return ambient + Color(0, 0, 0, 1) + Color(0, 0, 0, 1);
    }

    auto diffuse = effectiveColor * material.diffuse * lightNormalAngle;
    auto reflectDir = glm::reflect(-lightDir, normal);
    auto reflectEyeAngle = glm::dot(reflectDir, eye);

    auto factor = glm::pow(reflectEyeAngle, material.shininess);
    auto specular = light.getIntensity() * material.specular * factor;

    return ambient + diffuse + specular;
}

Ray RayTracerRenderer::rayForPixel(int x, int y) const {
    auto camera = m_world.getCamera();
    double xOffset = (x + 0.5) * camera.getPixelSize();
    double yOffset = (y + 0.5) * camera.getPixelSize();

    double worldX = camera.getHalfWidth() - xOffset;
    double worldY = camera.getHalfHeight() - yOffset;

    auto viewInverse = glm::inverse(camera.getViewMatrix());
    auto pixel = viewInverse * glm::dvec4(worldX, worldY, -1, 1);
    auto origin = viewInverse * glm::dvec4(0, 0, 0, 1);
    auto direction = glm::normalize(pixel - origin);

    return Ray(origin, direction);
}

World &RayTracerRenderer::getWorld() {
    return m_world;
}

bool RayTracerRenderer::isShadowed(const glm::dvec4 &point, const glm::dvec4 &normal) const {
    for (auto &light: m_world.getLights()) {
        auto v = light.getPosition() - point;
        auto distance = glm::length(v);
        auto direction = glm::normalize(v);

        auto ray = Ray { point, direction };
        auto intersections = m_world.intersect(ray);
        auto hit = intersections.hit();

        if (hit.has_value() && hit.value().distance < distance) {
            return true;
        }
    }
    return false;
}

