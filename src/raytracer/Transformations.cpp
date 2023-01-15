#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformations.h"

glm::mat4 Transformations::identity() {
    return glm::mat4(1);
}

glm::mat4 Transformations::translate(float x, float y, float z) {
    return translate({x,y,z});
}

glm::mat4 Transformations::translate(const glm::vec3 &factor) {
    return glm::translate(identity(), factor);
}

glm::mat4 Transformations::scale(float x, float y, float z) {
    return scale({ x, y, z });
}

glm::mat4 Transformations::scale(const glm::vec3 &factor) {
    return glm::scale(identity(), factor);
}

glm::mat4 Transformations::rotate(const float angle, const glm::vec3 &axes) {
    return glm::rotate(identity(), angle, axes);
}

