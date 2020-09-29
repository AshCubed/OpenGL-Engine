#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include "Game.h"

class FileReader {
private:
	std::vector<std::string> record;
	std::string fileName;

	//Textures
	std::vector<Texture*> fileReadTextures;
	std::vector<Material*> fileReadmaterials;
	//Models
	std::vector<Model*> fileReadModels;
	//Lights
	std::vector<PointLight*> fileReadPointLights;
	std::vector<DirLight*> fileReadDirLights;
	std::vector<SpotLight*> fileReadSpotLights;

	int col;
	int row;

	void ReturnColRow() {
		std::ifstream file(fileName);
		std::string line = "";
		this->col = 0;
		this->row = 0;
		int a = 0, b = 0;

		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string result;
			while (std::getline(iss, result, ';'))
			{
				if (col >= 8)
				{
					break;
				}
				else
				{
					this->col = this->col + 1;
				}

			}
			this->row = this->row + 1;
		}
	}

	void ReadFile() {
		ReturnColRow();
		std::stringstream ss;
		std::ifstream in_file(fileName);
		std::string line = "";
		std::string prefix = "";

		int objType = 0;
		int texNum = 0;
		int posX = 0;
		int posY = 0;
		int posZ = 0;
		int rotX = 0;
		int rotY = 0;
		int rotZ = 0;

		int counter = 0;
		while (std::getline(in_file, line, ';'))
		{
			counter++;
			ss.clear();
			ss.str(line);

			if (counter >= col + 1)
			{
				cout << objType << " ";
				cout << texNum << " ";
				cout << posX << " ";
				cout << posY << " ";
				cout << posZ << " ";
				cout << rotX << " ";
				cout << rotY << " ";
				cout << rotZ << "\n";

				//ObjType(objType, texNum, posX, posY, posZ);

				objType = 0;
				texNum = 0;
				posX = 0;
				posY = 0;
				posZ = 0;
				rotX = 0;
				rotY = 0;
				rotZ = 0;

				counter = 0;
				counter++;
			}
			if (counter == 1)
			{
				ss >> objType;
			}
			else if (counter == 2) {
				ss >> texNum;
			}
			else if (counter == 3) {
				ss >> posX;
			}
			else if (counter == 4) {
				ss >> posY;
			}
			else if (counter == 5) {
				ss >> posZ;
			}
			else if (counter == 6) {
				ss >> rotX;
			}
			else if (counter == 7) {
				ss >> rotY;
			}
			else if (counter == 8) {
				ss >> rotZ;
			}
		}
	}



public:
	FileReader( /*std::vector<Texture*> textures,
		std::vector<Material*> materials*/) {
		//this->fileName = fileName;
		//this->fileReadTextures = textures;
		//this->fileReadmaterials = materials;
		//this->ReadFile();
	}

	~FileReader() {

	}

	void ObjType(int objType, int texNum, int posX, int posY, int posZ) {
		switch (objType) {
		case 1:
			this->fileReadModels.push_back(new Model(
				glm::vec3(posX, posY, posZ),
				this->fileReadmaterials[0],
				this->fileReadTextures[ObjTex(texNum)],
				this->fileReadTextures[TEX_NANI_SPECULAR],
				"C:/Users/ashju/Desktop/GADE7312_WALLS.obj",
				glm::vec3(0.f, 90.f, 0.f)
			)
			);
			std::cout << "Model Created: walls" << "\n";
			break;
		case 2:
			this->fileReadModels.push_back(new Model(
				glm::vec3(posX, posY, posZ),
				this->fileReadmaterials[0],
				this->fileReadTextures[ObjTex(texNum)],
				this->fileReadTextures[TEX_NANI_SPECULAR],
				"C:/Users/ashju/Desktop/GADE7312_FLOOR.obj",
				glm::vec3(0.f, 90.f, 0.f)
			)
			);
			std::cout << "Model Created: Floor" << "\n";
			break;
		case 3:
			this->fileReadModels.push_back(new Model(
				glm::vec3(posX, posY, posZ),
				this->fileReadmaterials[0],
				this->fileReadTextures[ObjTex(texNum)],
				this->fileReadTextures[TEX_NANI_SPECULAR],
				"C:/Users/ashju/Desktop/GADE7312_Door.obj",
				glm::vec3(0.f, 90.f, 0.f)
			)
			);
			std::cout << "Model Created: Door" << "\n";
			break;
		case 4:
			this->fileReadSpotLights.push_back(new SpotLight(glm::vec3(posX, posY, posZ), glm::vec3(0.f, 90.f, 0.f)));
			std::cout << "Light Spot" << "\n";
			break;
		case 5:
			this->fileReadDirLights.push_back(new DirLight(glm::vec3(posX, posY, posZ), glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f)));
			std::cout << "Light Dir" << "\n";
			break;
		case 6:
			this->fileReadPointLights.push_back(new PointLight(glm::vec3(posX, posY, posZ)));
			std::cout << "Lght Point" << "\n";
			break;
		}
	}

	texture_enum ObjTex(int num) {
		switch (num) {
		case 1:
			return TEX_NANI;
		case 2:
			return TEX_NANI_SPECULAR;
		case 3:
			return TEX_SHREK;
		case 4:
			return TEX_SHREK_SPECULAR;
		case 5:
			return TEX_DOOR;
		case 6:
			return TEX_DOOR2;
		case 7:
			return TEX_DOOR3;
		case 8:
			return TEX_WALL;
		case 9:
			return TEX_PAINTWALL;
		case 10:
			return TEX_CEILING;
		case 11:
			return TEX_TILEDCEILING;
		case 12:
			return TEX_STONEFLOOR;
		case 13:
			return TEX_BRICKFLOOR;
		case 14:
			return TEX_GRASSFLOOR;
		}
	}
};
