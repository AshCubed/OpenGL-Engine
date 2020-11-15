#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "OBJLoader.h"
#include "Assimp.h"

class Model {
private:
	Material* material;
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	Texture* overrideTextureNorm;
	Texture* overrideTextureBump;


	glm::vec3 position;
	glm::vec3 rotation;

	void updateUniforms() {

	}


public:
	std::vector<Mesh*> meshes;

	Model(
		glm::vec3 position, 
		Material* material, 
		Texture* overrideTexDif, 
		Texture* overrideTexSpec,
		Texture* overrideTexNorm,
		Texture* overrideTexBump,
		std::vector<Mesh*> meshes,
		glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->material = material;
		this->overrideTextureDiffuse = overrideTexDif;
		this->overrideTextureSpecular = overrideTexSpec;

		for (auto* i : meshes) {
			this->meshes.push_back(new Mesh(*i));
		}

		this->updateMovement(this->position);
		this->updateRotation(this->rotation);
	}

	//OBJ File Loaded model
	Model(
		glm::vec3 position,
		Material* material,
		Texture* overrideTexDif,
		Texture* overrideTexSpec,
		Texture* overrideTexNorm,
		Texture* overrideTexBump,
		string obj_file,
		glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->material = material;
		this->overrideTextureDiffuse = overrideTexDif;
		this->overrideTextureSpecular = overrideTexSpec;
		this->overrideTextureNorm = overrideTexNorm;
		this->overrideTextureBump = overrideTexBump;

		ModelManager model = ModelManager();
		model.loadModel(obj_file);
		std::vector<Vertex> temp = *model.getVertexData();


		this->meshes.push_back(new Mesh(temp.data(), temp.size(), NULL, 0, glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)));

		this->updateMovement(this->position);
		this->updateRotation(this->rotation);
	}



	~Model() {
		for (auto*& i : meshes) {
			delete i;
		}
	}



	//Functions
	void updateRotation(const glm::vec3 rotation) {
		for (auto& i : this->meshes) {
			i->rotate(rotation);
		}
	}

	void updateMovement(glm::vec3 newPosition) {
		for (auto& i : this->meshes) {
			i->move(newPosition);
			i->setOrigin(newPosition);
		}
	}

	void render(Shader* shader) {
		//Update the Uniforms
		this->updateUniforms();

		//Update Uniforms
		this->material->sendToShader(*shader);

		//USE PROGRAM (BECAUSE SHADER CLASS LAST UNIFROM UPDATE UNUSES IT)
		shader->use();
		//shaderProgram.use();
		//glUseProgram(shaderProgram);

		//Draw
		for (auto& i : this->meshes) {

			//Activate Texture
			this->overrideTextureDiffuse->bind(0);
			this->overrideTextureSpecular->bind(1);
			//this->textures[TEX_SHREK_MMH1]->bind(1);

			i->render(shader); //Activate shader also
		}
	}

	
};
