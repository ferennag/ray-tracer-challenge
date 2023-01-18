#ifndef RAY_TRACER_CHALLENGE_SCENEPARSER_H
#define RAY_TRACER_CHALLENGE_SCENEPARSER_H

#include <memory>
#include <string_view>
#include "World.h"

namespace YAML {
    class Node;
}

class SceneParser {
public:
    std::unique_ptr<World> loadScene(std::string_view path);

    static glm::dvec3 parseVector(const YAML::Node &node);
    static glm::dmat4 parseTransformations(const YAML::Node &node);
    static std::unique_ptr<Pattern> parsePattern(const YAML::Node &node);
    static Material parseMaterial(const YAML::Node &node);
private:
};


#endif //RAY_TRACER_CHALLENGE_SCENEPARSER_H
