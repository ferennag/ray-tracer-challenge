#ifndef RAY_TRACER_CHALLENGE_MATERIAL_H
#define RAY_TRACER_CHALLENGE_MATERIAL_H

#include <glm/glm.hpp>
#include "../../engine/Color.h"

//http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
struct Material {
    Color color { 0.7, 0.4, 0.4, 1.0 };
    double ambient { 0.1 };
    double diffuse { 0.9 };
    double specular { 0.7  };
    double shininess { 120 };
};
#endif //RAY_TRACER_CHALLENGE_MATERIAL_H
