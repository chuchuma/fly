#include <map>
#include <stdio.h>
#include <string>
#include <vector>

#include "models.h"
#include "shaders.h"

using std::map;
using std::string;
using std::vector;

char const *const model_paths[2] = {
	"assets/test_model/nanosuit.obj",
    "assets/rock/Rock1.obj"
};
map<model_t, vector<Mesh> > models;
static string directory;
extern GLuint shaderProgram;

vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) {
    vector<Texture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        textures.push_back(getTexture(str.C_Str(), directory, typeName));
    }
    return textures;
}
Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vec;

        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vertex.pos = vec;
        
        vec.x = mesh->mNormals[i].x;
        vec.y = mesh->mNormals[i].y;
        vec.z = mesh->mNormals[i].z;
        vertex.norm = vec;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec1;
            vec1.x = mesh->mTextureCoords[0][i].x;
            vec1.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec1;
        } else {
            vertex.texCoords = glm::vec2(0.0, 0.0);
        }
        vertices.push_back(vertex);
    }

    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Mesh(vertices, indices, textures);
}
void processNode(aiNode* node, const aiScene* scene, model_t mod) {
    if (!node) {
        return;
    }
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
        models[mod].push_back(processMesh(mesh, scene)); 
    }
    for (GLuint i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, mod);
    }
}
bool ensureModel(model_t mod) {
    if (models.find(mod) != models.end()) {
        return true;
    }
    const char* path = model_paths[mod];
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
            path, aiProcess_Triangulate
              | aiProcess_FlipUVs
    );
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        fputs(importer.GetErrorString(), stderr);
        return false;
    }
    string path_str = string(path);
    directory = path_str.substr(0, path_str.find_last_of('/'));
    models[mod] = vector<Mesh>();
    processNode(scene->mRootNode, scene, mod);
    return true;
}
void drawModel(model_t model) {
    for (GLuint i = 0; i < models[model].size(); i++) {
        models[model][i].draw(shaderProgram);
    }
}
