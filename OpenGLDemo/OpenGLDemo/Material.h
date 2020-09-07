#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Shader.h"

class Material {
private:
    glm::vec3 ambient;
    glm::vec3 diffues;
    glm::vec3 specular;
    GLint diffuseTex;
    GLint specularTex;


public:
	Material(
    glm::vec3 ambient,
    glm::vec3 diffues,
    glm::vec3 specular,
    GLint diffuseTex,
    GLint specularTex){
        this->ambient = ambient;
        this->diffues = diffues;
        this->specular = specular;
        this->diffuseTex = diffuseTex;
        this->specularTex = specularTex;
	}

    ~Material(){}

    //Function
    void sendToShader(Shader& programID) {
        programID.setVec3f(this->ambient, "material.ambient");
        programID.setVec3f(this->diffues, "material.diffues");
        programID.setVec3f(this->specular, "material.specular");
        programID.set1i(this->diffuseTex, "material.diffuseTex");
        programID.set1i(this->specularTex, "material.specularTex");
    }
};
