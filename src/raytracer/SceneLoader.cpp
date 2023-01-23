#include <yaml-cpp/yaml.h>
#include <map>
#include <exception>
#include <ranges>
#include "SceneLoader.h"
#include "shapes/Plane.h"
#include "shapes/Sphere.h"
#include "Transformations.h"
#include "lighting/patterns/CheckersPattern.h"
#include "lighting/patterns/GradientPattern.h"
#include "shapes/Cube.h"
#include "shapes/Cylinder.h"
#include "shapes/Cone.h"
#include "shapes/Group.h"
#include "shapes/Triangle.h"
#include "ObjLoader.h"

glm::dvec3 SceneLoader::parseVector(const YAML::Node &node) {
    glm::dvec3 result { node[0].as<double>(), node[1].as<double>(), node[2].as<double>() };
    return result;
}

glm::dmat4 SceneLoader::parseTransformations(const YAML::Node &node) {
    auto result = glm::identity<glm::dmat4>();

    if (!node) {
        return result;
    }

    std::vector<glm::dmat4> transformations;

    for (YAML::const_iterator it = node.begin(); it != node.end(); ++it) {
        auto transform = *it;
        auto transformType = transform[0].as<std::string>();

        if (transformType == "scale") {
            transformations.push_back(Transformations::scale(transform[1].as<double>(), transform[2].as<double>(),
                                                             transform[3].as<double>()));
            continue;
        }

        if (transformType == "translate") {
            transformations.push_back(Transformations::translate(transform[1].as<double>(), transform[2].as<double>(),
                                                                 transform[3].as<double>()));
            continue;
        }

        if (transformType == "rotate-x") {
            transformations.push_back(Transformations::rotate(transform[1].as<double>(), { 1, 0, 0 }));
            continue;
        }

        if (transformType == "rotate-y") {
            transformations.push_back(Transformations::rotate(transform[1].as<double>(), { 0, 1, 0 }));
            continue;
        }

        if (transformType == "rotate-z") {
            transformations.push_back(Transformations::rotate(transform[1].as<double>(), { 0, 0, 1 }));
            continue;
        }

        throw std::runtime_error("Invalid transform : " + transformType);
    }

    for (auto &transformation: std::ranges::reverse_view(transformations)) {
        result *= transformation;
    }

    return result;
}

std::unique_ptr<Pattern> SceneLoader::parsePattern(const YAML::Node &node) {
    if (!node) {
        return nullptr;
    }

    std::unique_ptr<Pattern> result;

    auto type = node["type"].as<std::string>();
    auto color1 = Color(parseVector(node["colors"][0]));
    auto color2 = Color(parseVector(node["colors"][1]));
    auto transform = SceneLoader::parseTransformations(node["transform"]);

    if (type == "checkers") {
        result = std::make_unique<CheckersPattern>(color1, color2);
        result->withTransformation(transform);
    } else if (type == "stripes") {
        result = std::make_unique<StripePattern>(color1, color2);
        result->withTransformation(transform);
    } else if (type == "gradient") {
        result = std::make_unique<GradientPattern>(color1, color2);
        result->withTransformation(transform);
    }

    return result;
}

Material SceneLoader::parseMaterial(const YAML::Node &node, const std::map<std::string, Material> &definitions,
                                    const Material &extended) {
    if (!node) {
        return extended;
    }

    if (!node.IsMap()) {
        auto name = node.as<std::string>();
        return definitions.find(name)->second;
    }

    Material material = extended;

    if (node["color"]) {
        glm::dvec3 color = SceneLoader::parseVector(node["color"]);
        material.color = Color(color.x, color.y, color.z);
    }

    if (node["ambient"]) {
        material.ambient = node["ambient"].as<double>();
    }

    if (node["diffuse"]) {
        material.diffuse = node["diffuse"].as<double>();
    }

    if (node["specular"]) {
        material.specular = node["specular"].as<double>();
    }

    if (node["shininess"]) {
        material.shininess = node["shininess"].as<double>();
    }

    if (node["reflective"]) {
        material.reflectivity = node["reflective"].as<double>();
    }

    if (node["transparency"]) {
        material.transparency = node["transparency"].as<double>();
    }

    if (node["refractive-index"]) {
        material.refractiveIndex = node["refractive-index"].as<double>();
    }

    if (node["pattern"]) {
        material.pattern = std::move(SceneLoader::parsePattern(node["pattern"]));
    }

    return material;
}

std::unique_ptr<World> SceneLoader::loadDefaultScene() {
    return loadScene("../resources/default-scene.yaml");
}

std::unique_ptr<World> SceneLoader::loadScene(std::string_view path) {
    auto world = std::make_unique<World>();
    YAML::Node scene = YAML::LoadFile(path.data());

    std::map<std::string, Material> materialDefinitions;

    for (YAML::const_iterator it = scene.begin(); it != scene.end(); ++it) {
        auto node = *it;
        if (node["define"]) {
            auto name = node["define"].as<std::string>();
            Material extended;

            if (node["extend"]) {
                extended = materialDefinitions.find(node["extend"].as<std::string>())->second;
            }

            auto material = parseMaterial(node["value"], materialDefinitions, extended);
            materialDefinitions.insert({ name, material });
        }
    }

    for (YAML::const_iterator it = scene.begin(); it != scene.end(); ++it) {
        auto node = *it;

        if (node["add"]) {
            auto type = node["add"].as<std::string>();
            if (type == "camera") {
                auto width = node["width"].as<int>();
                auto height = node["height"].as<int>();
                auto fov = node["field-of-view"].as<double>();
                glm::dvec3 position = SceneLoader::parseVector(node["from"]);
                glm::dvec3 target = SceneLoader::parseVector(node["to"]);
                auto camera = Camera(width, height, fov);
                camera.setPosition(position);
                camera.setTarget(target);
                world->setCamera(camera);
            } else if (type == "light") {
                glm::dvec3 position = SceneLoader::parseVector(node["at"]);
                glm::dvec3 intensity = SceneLoader::parseVector(node["intensity"]);
                auto light = PointLight(position, intensity);
                world->addLight(light);
            } else {
                auto shape = parseShape(node, materialDefinitions);
                world->addObject(shape);
            }
        }
    }

    return world;
}

std::shared_ptr<Shape>
SceneLoader::parseShape(const YAML::Node &node, const std::map<std::string, Material> &materialDefinitions,
                        Shape *parent) {
    auto type = node["add"].as<std::string>();
    if (type == "group") {
        auto group = std::make_shared<Group>(parent);
        group->withTransformation(SceneLoader::parseTransformations(node["transform"]));

        if (node["children"]) {
            auto children = node["children"];
            for (YAML::const_iterator it = children.begin(); it != children.end(); ++it) {
                auto node = *it;
                auto shape = parseShape(node, materialDefinitions, group.get());
                group->addChild(shape);
            }
        }

        group->subdivide(1);

        return group;
    } else if (type == "obj") {
        auto objGroup = ObjLoader::loadObjFile(node["file"].as<std::string>());
        objGroup->withTransformation(SceneLoader::parseTransformations(node["transform"]));
        objGroup->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        objGroup->subdivide(1);
        return objGroup;
    } else if (type == "plane") {
        auto plane = std::make_shared<Plane>(parent);
        plane->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        plane->withTransformation(SceneLoader::parseTransformations(node["transform"]));
        return plane;
    } else if (type == "sphere") {
        auto sphere = std::make_shared<Sphere>(parent);
        sphere->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        sphere->withTransformation(SceneLoader::parseTransformations(node["transform"]));
        return sphere;
    } else if (type == "cube") {
        auto cube = std::make_shared<Cube>(parent);
        cube->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        cube->withTransformation(SceneLoader::parseTransformations(node["transform"]));
        return cube;
    } else if (type == "cylinder") {
        auto cylinder = std::make_shared<Cylinder>(parent);
        cylinder->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        cylinder->withTransformation(SceneLoader::parseTransformations(node["transform"]));

        if (node["minimum"]) {
            cylinder->setMinimum(node["minimum"].as<double>());
        }

        if (node["maximum"]) {
            cylinder->setMaximum(node["maximum"].as<double>());
        }

        if (node["closed"]) {
            cylinder->setClosed(node["closed"].as<bool>());
        }

        return cylinder;
    } else if (type == "cone") {
        auto cone = std::make_shared<Cone>(parent);
        cone->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        cone->withTransformation(SceneLoader::parseTransformations(node["transform"]));

        if (node["minimum"]) {
            cone->setMinimum(node["minimum"].as<double>());
        }

        if (node["maximum"]) {
            cone->setMaximum(node["maximum"].as<double>());
        }

        if (node["closed"]) {
            cone->setClosed(node["closed"].as<bool>());
        }

        return cone;
    } else if (type == "triangle") {
        glm::dvec4 a = { parseVector(node["points"][0]), 1 };
        glm::dvec4 b = { parseVector(node["points"][1]), 1 };
        glm::dvec4 c = { parseVector(node["points"][2]), 1 };

        auto triangle = std::make_shared<Triangle>(a, b, c, parent);
        triangle->withMaterial(SceneLoader::parseMaterial(node["material"], materialDefinitions));
        triangle->withTransformation(SceneLoader::parseTransformations(node["transform"]));
        return triangle;
    }
}
