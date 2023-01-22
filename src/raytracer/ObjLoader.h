#ifndef RAY_TRACER_CHALLENGE_OBJLOADER_H
#define RAY_TRACER_CHALLENGE_OBJLOADER_H

#include <memory>
#include <string_view>
#include "shapes/Group.h"

class ObjLoader {
public:
    ObjLoader(const ObjLoader &other) = delete;
    ObjLoader(const ObjLoader &&other) = delete;
    ObjLoader &operator=(const ObjLoader &other) = delete;
    ObjLoader &operator=(const ObjLoader &&other) = delete;

    static std::unique_ptr<Group> loadObjFile(std::string_view path);

private:
    ObjLoader() = default;
};


#endif //RAY_TRACER_CHALLENGE_OBJLOADER_H
