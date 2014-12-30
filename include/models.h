#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

enum model_t {
	SUIT
};
bool ensureModel(model_t);
void drawModel(model_t);
