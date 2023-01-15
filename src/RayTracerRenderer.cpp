#include "RayTracerRenderer.h"
#include "raytracer/Ray.h"
#include "raytracer/Sphere.h"

RayTracerRenderer::RayTracerRenderer(int width, int height) : Renderer(width, height) {
}

void RayTracerRenderer::render() {
    clear();

    glm::vec3 rayOrigin { 0, 0, -5 };
    float wallZ { 5 }, wallSize { 7.0 };
    float half { wallSize / 2 };
    glm::vec2 pixelSize { wallSize / static_cast<float>(m_width), wallSize / static_cast<float>(m_height) };

    std::vector<PointLight> lights = m_world.getLights();
    for (int y = 0; y < m_height; ++y) {
        float worldY = half - pixelSize.y * y;
        for (int x = 0; x < m_width; ++x) {
            float worldX = -half + pixelSize.x * x;
            glm::vec3 position { worldX, worldY, wallZ };
            Ray ray(rayOrigin, glm::normalize(position - rayOrigin));
            m_eye = -ray.getDirection();
            auto intersections = m_world.intersect(ray);
            auto hit = intersections.hit();

            if (hit.has_value()) {
                auto intersection = hit.value();
                auto point = ray.at(intersection.distance);
                Color finalColor { 0, 0, 0, 1 };
                for (auto &light: lights) {
                    finalColor += lighting(*intersection.object, light, point);
                }
                m_buffer[y][x].copy(finalColor);
            }
        }
    }
}

Color RayTracerRenderer::lighting(const Sphere &sphere, const PointLight &light, const glm::vec4 &point) const {
    auto material = sphere.getMaterial();
    auto normal = sphere.getNormalAt(point);
    auto effectiveColor = material.color * light.getIntensity();
    auto lightDir = glm::normalize(light.getPosition() - point);
    auto ambient = effectiveColor * material.ambient;
    auto lightNormalAngle = glm::dot(lightDir, normal);

    if (lightNormalAngle < 0) {
        return ambient + Color(0, 0, 0, 1) + Color(0, 0, 0, 1);
    }

    auto diffuse = effectiveColor * material.diffuse * lightNormalAngle;
    auto reflectDir = glm::reflect(-lightDir, normal);
    auto reflectEyeAngle = glm::dot(reflectDir, m_eye);

    auto factor = glm::pow(reflectEyeAngle, material.shininess);
    auto specular = light.getIntensity() * material.specular * factor;

    return ambient + diffuse + specular;
}
