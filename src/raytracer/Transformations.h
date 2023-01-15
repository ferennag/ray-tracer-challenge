#ifndef RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
#define RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H

#include <glm/glm.hpp>

class Transformations {
public:
    Transformations() = delete;
    Transformations(const Transformations &other) = delete;
    Transformations(const Transformations &&other) = delete;

    static glm::mat4 identity();
    static glm::mat4 translate(float x, float y, float z);
    static glm::mat4 translate(const glm::vec3 &factor);
    static glm::mat4 scale(float x, float y, float z);
    static glm::mat4 scale(const glm::vec3 &factor);
    static glm::mat4 rotate(const float angle, const glm::vec3 &axes);
private:
};


#endif //RAY_TRACER_CHALLENGE_TRANSFORMATIONS_H
