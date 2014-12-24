#include <stdio.h>
#include "models.h"
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <map>
using std::map;
char const *const model_paths[1] = {
	"assets/test.blend"
};
map<model_t, const aiScene*> scenes;
const aiScene* getScene(model_t model) {
    ensureModel(model);
    return scenes[model];
}

bool ensureModel(model_t mod) {
    if (scenes.find(mod) != scenes.end()) {
        return true;
    }
    const char* path = model_paths[mod];
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_CalcTangentSpace
              | aiProcess_Triangulate
              | aiProcess_JoinIdenticalVertices
              | aiProcess_SortByPType
              | aiProcess_ValidateDataStructure
              | aiProcess_FindInvalidData
    );
    if (!scene) {
        std::cout << importer.GetErrorString() << std::endl;
        fputs(importer.GetErrorString(), stderr);
        return false;
    }
    scenes[mod] = scene;
    return true;
}
