#include <assimp/scene.h>

enum model_t {
	TEST
};
bool ensureModel(model_t);
const aiScene* getScene(model_t);
