#pragma once
#include <SOIL.h>
#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
using namespace std;
class Model {
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
public:
	Model();
	Model(GLchar* path);
	void loadModel(string path);
	void Draw(Shader shader, GLint drawMode);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLint TextureFromFile(const char* path, string directory);
};