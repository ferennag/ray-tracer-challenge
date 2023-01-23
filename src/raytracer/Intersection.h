#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

#include "../engine/util/RayMath.h"

class Shape;

struct Intersection {
    double distance;
    const Shape *object;
    double u, v;

    bool operator==(const Intersection &rhs) const {
        return object == rhs.object && doubleEq(distance, rhs.distance);
    }
};

#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H
