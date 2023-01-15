#ifndef RAY_TRACER_CHALLENGE_MATERIAL_H
#define RAY_TRACER_CHALLENGE_MATERIAL_H

#include <glm/glm.hpp>
#include "../engine/Color.h"

//http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
struct Material {
    Color color { 0.7, 0.4, 0.4, 1.0 };
    float ambient { 0.1 };
    float diffuse { 0.9 };
    float specular { 0.7  };
    float shininess { 120 };
};
#endif //RAY_TRACER_CHALLENGE_MATERIAL_H
