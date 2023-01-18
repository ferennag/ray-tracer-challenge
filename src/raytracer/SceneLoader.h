#ifndef RAY_TRACER_CHALLENGE_SCENELOADER_H
#define RAY_TRACER_CHALLENGE_SCENELOADER_H

#include <map>
#include <memory>
#include <string_view>
#include "World.h"

namespace YAML {
    class Node;
}

class SceneLoader {
public:
    SceneLoader(const SceneLoader &other) = delete;
    SceneLoader(const SceneLoader &&other) = delete;
    SceneLoader &operator=(const SceneLoader &other) = delete;
    SceneLoader &operator=(const SceneLoader &&other) = delete;

    static std::unique_ptr<World> loadScene(std::string_view path);
    static std::unique_ptr<World> loadDefaultScene();
    static glm::dvec3 parseVector(const YAML::Node &node);
    static glm::dmat4 parseTransformations(const YAML::Node &node);
    static std::unique_ptr<Pattern> parsePattern(const YAML::Node &node);
    static Material parseMaterial(const YAML::Node &node, const std::map<std::string, Material> &definitions,
                                  const Material &extended = Material());
private:
    SceneLoader() = default;
};


#endif //RAY_TRACER_CHALLENGE_SCENELOADER_H
