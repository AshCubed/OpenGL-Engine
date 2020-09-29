#pragma once
#include"libs.h"
#include "Camera.h"

//ENUMERATIONS
enum shader_enums {
	SHADER_CORE_PROGRAM = 0
};
enum texture_enum {
	TEX_NANI = 0, TEX_NANI_SPECULAR, TEX_SHREK, TEX_SHREK_SPECULAR, 
	TEX_DOOR,TEX_DOOR2, TEX_DOOR3, TEX_WALL, TEX_PAINTWALL, TEX_CEILING, TEX_TILEDCEILING, TEX_STONEFLOOR,
	TEX_BRICKFLOOR, TEX_GRASSFLOOR
};
enum material_enum {
	MAT_1 = 0
};
enum mesh_enum {
	MESH_QUAD = 0
};

class Game
{
private:
//Variables
	//Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int frameBufferWidth;
	int frameBufferHeight;
	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;
	//Delta Time
	float dt;
	float curTime;
	float lastTime;
	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//Camera
	Camera camera;

	//Matricies
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	//Models
	std::vector<Model*> models;

	//Lights
	std::vector<PointLight*> pointLights;
	std::vector<DirLight*> dirLights;
	std::vector<SpotLight*> spotLights;

	//FOR FPS COUNTER
	double lastFPSTime;
	int nbFrames;

	//for file reading
	int col;
	int row;

//Private Functions
	void initGLFW();
	void initWindow(const char* title, bool resizeable);
	void initGLAD();	//AFTER CONTECT CREATION!!!!
	void initOpenGLOptions();
	void initMatricies();
	void initShaders();
	void initTextures();
	void initMaterials();

	//Level file reading
	void initReadLevelCols();
	void initReadLevelFile();
	void ObjType(int objType, int texNum, int posX, int posY, int posZ);
	texture_enum ObjTex(int num);

	void initModels();
	void initLights();
	void initUniforms();

	void updateUniforms();
	//Inputs
	void updateKeyboardInputs();
	void updateDT();
	void updateMouseInputs();
	void updateInput();


//Static Variables

public:
//Constructors / Destructors
	Game(
		const char* title, const int WINDOW_WIDTH,
		const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR,
		const int GL_VERSION_MINOR, bool resizeable);

	virtual ~Game();

//Accessors
	int getWindowShouldClose();

//Modifies
	void setWindowShouldClose();

//Functions
	void update();
	void render();
	void fpsCounter();


//Static Functions
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};



