#include <iostream>
#include <thread>
#include <future>
#include <glm/gtc/matrix_transform.hpp>
#include "RayTracerRenderer.h"
#include "Ray.h"
#include "util/RayMath.h"
#include "shapes/Sphere.h"

RayTracerRenderer::RayTracerRenderer(int width, int height) : Renderer(width, height), m_world(width, height) {
}

void RayTracerRenderer::render() {
    const auto maxThreads = std::thread::hardware_concurrency();
    // The number of blocks in each row/column to render separately
    // In total we want as many blocks as threads are available
    const auto blockCount = floor(sqrt(maxThreads));
    const auto dx = m_width / blockCount;
    const auto dy = m_height / blockCount;

    std::vector<std::future<void>> threads;
    for (int row = 0; row < blockCount; ++row) {
        for (int col = 0; col < blockCount; ++col) {
            auto minX = col * dx;
            auto maxX = col * dx + dx;
            auto minY = row * dy;
            auto maxY = row * dy + dy;
            std::promise<void> promise;
            threads.push_back(promise.get_future());
            std::thread thread(&RayTracerRenderer::renderArea, this, minX, minY, maxX, maxY, std::move(promise));
            thread.detach();
        }
    }

    // Wait for the full scene to be rendered, otherwise there will be artifacts
    for (auto &future: threads) {
        future.wait();
    }
}

/**
 * Renders only a specific rectangular area of the scene. Sets the value of the promise when the rendering completed.
 */
void RayTracerRenderer::renderArea(int minX, int minY, int maxX, int maxY, std::promise<void> result) {
    for (int y = minY; y < maxY; ++y) {
        for (int x = minX; x < maxX; ++x) {
            auto ray = rayForPixel(x, y);
            auto color = colorAt(ray);
            // We are not changing the content of the vector (only the values in the objects stored in the vector),
            // so this is considered a reading operation from the vector's perspective.
            // Thus, this operation is thread safe, no need for mutex.
            m_buffer[y][x].copy(color);
        }
    }
    result.set_value();
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


Color RayTracerRenderer::lighting(const Shape &shape, const PointLight &light, const glm::dvec4 &eye,
                                  const glm::dvec4 &point) const {
    auto material = shape.getMaterial();
    auto normal = shape.getNormalAt(point);
    auto overPoint = point + normal * PRECISION;
    if (isShadowed(overPoint, normal)) {
        return { 0.0, 0.0, 0.0, 1.0 };
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

    auto viewInverse = camera.getInverseViewMatrix();
    auto pixel = viewInverse * glm::dvec4(worldX, worldY, -1, 1);
    auto origin = viewInverse * glm::dvec4(0, 0, 0, 1);
    auto direction = glm::normalize(pixel - origin);

    return Ray(origin, direction);
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
