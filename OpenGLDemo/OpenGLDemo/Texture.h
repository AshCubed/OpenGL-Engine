#pragma once

#include<iostream>
#include<string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<SOIL2.h>

using namespace std;

class Texture {
private:
	GLuint id;
	int height;
	int width;
    unsigned int type;
    GLint textureUnit;


public:
	Texture(const char* fileName, GLenum type, GLint texture_Unit) {
        this->type = type;
        this->textureUnit = texture_Unit;

        //load the imahe
        unsigned char* image = SOIL_load_image(fileName,&this->width, &this->height, NULL, SOIL_LOAD_RGBA);

        //generate the texture into our ID
        glGenTextures(1, &this->id);
        glBindTexture(type, this->id);

        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (image != NULL)
        {
            glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(type);
        }
        else
        {
            cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << fileName << "\n";
        }

        glActiveTexture(0);
        glBindTexture(type, 0);
        SOIL_free_image_data(image);
	}

	~Texture() {
		glDeleteTextures(1, &this->id);
	}

    GLuint getID() const {return this->id;}


    //Dynamicall choose what texture unit to use
    void bind() {
        glActiveTexture(GL_TEXTURE0 + this-> textureUnit);
        glBindTexture(type, this->id);
    }

    void unBind() {
        glActiveTexture(0);
        glBindTexture(this->type, 0);
    }

    GLint getTextureUnit() const {
        return this->textureUnit;
    }

    void loadFromFile(const char* fileName) {

        if (this->id)
        {
            glDeleteTextures(1, &this->id);
        }

        //load the imahe
        unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

        //generate the texture into our ID
        glGenTextures(1, &this->id);
        glBindTexture(type, this->id);

        glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        if (image != NULL)
        {
            glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(this->type);
        }
        else
        {
            cout << "ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED" << fileName << "\n";
        }

        glActiveTexture(0);
        glBindTexture(this->type, 0);
        SOIL_free_image_data(image);
    }
};
