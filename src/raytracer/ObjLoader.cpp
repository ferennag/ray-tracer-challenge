#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm.hpp>
#include "ObjLoader.h"
#include "shapes/Triangle.h"

static glm::dvec4 convertAiVertex(const aiVector3D &vec) {
    return { vec.x, vec.y, vec.z, 1 };
}

static glm::dvec4 convertAiVector(const aiVector3D &vec) {
    return { vec.x, vec.y, vec.z, 0 };
}

std::unique_ptr<Group> ObjLoader::loadObjFile(std::string_view path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices |
                                                          aiProcess_SortByPType | aiProcess_GenNormals);

    if (scene == nullptr) {
        return nullptr;
    }

    auto mainGroup = std::make_unique<Group>();

    for (int m = 0; m < scene->mNumMeshes; ++m) {
        auto group = std::make_shared<Group>();
        auto *mesh = scene->mMeshes[m];

        for (int f = 0; f < mesh->mNumFaces; ++f) {
            auto face = mesh->mFaces[f];
            auto v1 = convertAiVertex(mesh->mVertices[face.mIndices[0]]);
            auto v2 = convertAiVertex(mesh->mVertices[face.mIndices[1]]);
            auto v3 = convertAiVertex(mesh->mVertices[face.mIndices[2]]);
            auto triangle = std::make_shared<Triangle>(v1, v2, v3, group.get());
            group->addChild(triangle);
        }

        mainGroup->addChild(group);
    }

    return mainGroup;
}
