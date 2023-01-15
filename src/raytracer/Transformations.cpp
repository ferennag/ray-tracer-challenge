#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformations.h"

glm::dmat4 Transformations::identity() {
    return glm::dmat4(1);
}

glm::dmat4 Transformations::translate(double x, double y, double z) {
    return translate({x,y,z});
}

glm::dmat4 Transformations::translate(const glm::dvec3 &factor) {
    return glm::translate(identity(), factor);
}

glm::dmat4 Transformations::scale(double x, double y, double z) {
    return scale({ x, y, z });
}

glm::dmat4 Transformations::scale(const glm::dvec3 &factor) {
    return glm::scale(identity(), factor);
}

glm::dmat4 Transformations::rotate(const double angle, const glm::dvec3 &axes) {
    return glm::rotate(identity(), angle, axes);
}

