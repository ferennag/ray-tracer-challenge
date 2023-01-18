#ifndef RAY_TRACER_CHALLENGE_MATERIAL_H
#define RAY_TRACER_CHALLENGE_MATERIAL_H

#include <memory>
#include <glm/glm.hpp>
#include "../../engine/Color.h"
#include "patterns/Pattern.h"
#include "patterns/StripePattern.h"

//http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
struct Material {
    Color color { 1.0, 1.0, 1.0, 1.0 };
    double ambient { 0.1 };
    double diffuse { 0.9 };
    double specular { 0.9 };
    double shininess { 200 };
    double reflectivity { 0.0 };
    double transparency { 0.0 };
    double refractiveIndex { 1.0 };
    std::shared_ptr<Pattern> pattern { nullptr };
};
#endif //RAY_TRACER_CHALLENGE_MATERIAL_H
