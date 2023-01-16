#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

class Shape;

struct Intersection {
    double distance;
    const Shape *object;
};

#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H
