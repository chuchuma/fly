#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "mesh.h"

enum model_t {
	SUIT,
    ROCK
};
bool ensureModel(model_t);
void drawModel(model_t);
