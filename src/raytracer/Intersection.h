#ifndef RAY_TRACER_CHALLENGE_INTERSECTION_H
#define RAY_TRACER_CHALLENGE_INTERSECTION_H

class Sphere;

struct Intersection {
    double distance;
    const Sphere *object;
};

#endif //RAY_TRACER_CHALLENGE_INTERSECTION_H
