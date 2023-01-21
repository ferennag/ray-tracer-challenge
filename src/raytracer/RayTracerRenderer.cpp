#include <random>
#include <iostream>
#include <algorithm>
#include <thread>
#include <future>
#include <gtc/matrix_transform.hpp>
#include "RayTracerRenderer.h"
#include "Ray.h"
#include "shapes/Sphere.h"

RayTracerRenderer::RayTracerRenderer(int width, int height) : Renderer(width, height) {
    m_world = std::make_unique<World>();
    std::random_device seeder;
    const auto seed { seeder.entropy() ? seeder() : time(nullptr) };
    m_randEngine = std::mt19937_64 { static_cast<std::mt19937_64::result_type >(seed) };
}

void RayTracerRenderer::render() {
    const auto maxThreads = std::thread::hardware_concurrency();
    // The number of blocks in each row/column to render separately
    // We will use twice the amount of blocks based on the available threads
    const auto blockCount = floor(sqrt(maxThreads)) * 2;
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
            std::vector<Color> colors;
            colors.push_back(colorAt(rayForPixel(x, y), reflectionDepthLimit));

            auto range = 2.0;
            auto sampleSize = range / samples;
            for (int i = 0; i < samples; ++i) {
                for (int j = 0; j < samples; ++j) {
                    auto dx = -range / 2.0 + j*sampleSize;
                    auto dy = -range / 2.0 + i*sampleSize;
                    auto ray = rayForPixel(x + dx, y + dy);
                    colors.push_back(colorAt(ray, reflectionDepthLimit));
                }
            }

            auto average = std::accumulate(colors.begin(), colors.end(), colors[0], [](const Color &lhs, const Color &rhs) {
                return lhs.mix(rhs);
            });

            // We are not changing the content of the vector (only the values in the objects stored in the vector),
            // so this is considered a reading operation from the vector's perspective.
            // Thus, this operation is thread safe, no need for mutex.
            m_buffer[y][x].copy(average);
        }
    }
    result.set_value();
}


Color RayTracerRenderer::colorAt(const Ray &ray, const int remaining) const {
    auto intersections = m_world->intersect(ray);
    auto hit = intersections.hit();

    if (hit.has_value()) {
        auto computations = prepareComputations(hit.value(), intersections, ray);

        Color finalColor { 0, 0, 0, 1 };
        for (auto &light: m_world->getLights()) {
            finalColor += lighting(light, computations);
        }

        auto reflection = reflectedColor(computations, remaining);
        auto refraction = refractedColor(computations, remaining);
        auto material = computations.object->getMaterial();

        if (material.reflectivity > 0 && material.transparency > 0) {
            auto reflectance = computations.schlick();
            return finalColor + (reflection * reflectance) + (refraction * (1.0 - reflectance));
        } else {
            return finalColor + reflection + refraction;
        }
    } else {
        return Color::black();
    }
}

Color RayTracerRenderer::lighting(const PointLight &light, const Computations &comps) const {
    auto &material = comps.object->getMaterial();
    auto effectiveColor = comps.object->getColorAt(comps.overPoint) * light.getIntensity();
    auto ambient = effectiveColor * material.ambient;

    if (isShadowed(comps.overPoint)) {
        return ambient;
    }

    auto lightDir = glm::normalize(light.getPosition() - comps.overPoint);
    auto lightNormalAngle = glm::dot(lightDir, comps.normal);

    if (lightNormalAngle < 0) {
        return ambient;
    }

    auto diffuse = effectiveColor * material.diffuse * lightNormalAngle;
    auto reflectDir = glm::reflect(-lightDir, comps.normal);
    auto reflectEyeAngle = glm::dot(reflectDir, comps.eye);

    auto factor = glm::pow(reflectEyeAngle, material.shininess);
    auto specular = light.getIntensity() * material.specular * factor;

    return ambient + diffuse + specular;
}

Color RayTracerRenderer::reflectedColor(const Computations &comps, const int remaining) const {
    auto material = comps.object->getMaterial();
    if (absd(material.reflectivity) < PRECISION || remaining <= 0) {
        return Color::black();
    }

    auto reflectRay = Ray(comps.overPoint, comps.reflect);
    return colorAt(reflectRay, remaining - 1) * material.reflectivity;
}

Color RayTracerRenderer::refractedColor(const Computations &comps, const int remaining) const {
    auto material = comps.object->getMaterial();
    if (doubleEq(material.transparency, 0.0) || remaining <= 0) {
        return Color::black();
    }

    auto normal = comps.normal;
    auto nRatio = comps.n1 / comps.n2;
    auto cosI = glm::dot(comps.eye, normal);
    auto sin2T = pow(nRatio, 2.0) * (1.0 - pow(cosI, 2.0));

    // Total internal refraction
    if (sin2T > 1.0) {
        return Color::black();
    }

    auto cosT = sqrt(1.0 - sin2T);
    auto direction = normal * (nRatio * cosI - cosT) - comps.eye * nRatio;
    auto refractRay = Ray(comps.underPoint, direction);
    return colorAt(refractRay, remaining - 1) * material.transparency;
}

Ray RayTracerRenderer::rayForPixel(double x, double y) const {
    auto camera = m_world->getCamera();
    double xOffset = (x + 0.5) * camera.getPixelSize();
    double yOffset = (y + 0.5) * camera.getPixelSize();

    double worldX = camera.getHalfWidth() - xOffset;
    double worldY = camera.getHalfHeight() - yOffset;

    auto viewInverse = camera.getInverseViewMatrix();
    auto pixel = viewInverse * glm::dvec4(worldX, worldY, -1, 1);
    auto origin = viewInverse * glm::dvec4(0, 0, 0, 1);
    auto direction = glm::normalize(pixel - origin);

    return { origin, direction };
}

bool RayTracerRenderer::isShadowed(const glm::dvec4 &point) const {
    for (auto &light: m_world->getLights()) {
        auto v = light.getPosition() - point;
        auto distance = glm::length(v);
        auto direction = glm::normalize(v);

        auto ray = Ray { point, direction };
        auto intersections = m_world->intersect(ray);
        auto hit = intersections.hit();

        if (hit.has_value() && hit.value().distance < distance) {
            return true;
        }
    }
    return false;
}