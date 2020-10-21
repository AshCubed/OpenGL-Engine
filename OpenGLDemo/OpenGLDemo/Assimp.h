#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>
#include <assimp/cimport.h>

#include <Windows.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include "Vertex.h"

//GLFW
#include <GLFW/glfw3.h>

class ModelManager
{
public:
	ModelManager();
	~ModelManager(void);
	
	bool loadModel(std::string file);
	bool processData();
	std::vector<Vertex> *getVertexData();
	std::vector<GLint> *getIndexData();

private:
	bool assimpGetMeshData(const aiMesh *mesh);
private:
	Assimp::Importer         importer;
	const aiScene            *modelScene;
	const aiNode             *modelNode;
	const aiMesh             *modelMesh;
	const aiFace             *modelFace;
	std::vector<Vertex>      vertexBuff;
	std::vector<GLint>       indexBuff;

	std::vector<const aiNode*>  nodeBuff;
	unsigned int                numNodeBuff;
};

