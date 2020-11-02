#include "Game.h"
#include <stdlib.h>
#include <string.h>

float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};
vector<std::string> faces {
    "Textures/right.jpg",
    "Textures/left.jpg",
    "Textures/top.jpg",
    "Textures/bottom.jpg",
    "Textures/front.jpg",
    "Textures/back.jpg"
};
float cubeVertices[] = {
    // positions          // normals
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

//Private Functions
void Game::initGLFW()
{
    //INIT GLFW
    if (!glfwInit())
    {
        std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
        glfwTerminate();
    }
}

void Game::initWindow(const char* title, bool resizeable)
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, resizeable);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MAC OS


    this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

    if (this->window == nullptr)
    {
        std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
        glfwTerminate();
    }

    glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
    glfwSetFramebufferSizeCallback(window, Game::framebuffer_size_callback);
    //IMPORTANT WHITH PERSPECTIVE MATRIX!!!

    //glViewport(0, 0, framebufferWidth, framebufferHeight);

    glfwMakeContextCurrent(this->window); //IMPORTANT!!
}

void Game::initGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
}

void Game::initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST);

    //glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Input
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::initMatricies()
{
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::lookAt(this->camPosition,
        this->camPosition + this->camFront, this->worldUp);

    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(glm::radians(this->fov),
        static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
        this->nearPlane, this->farPlane);
}

void Game::initShaders()
{
    this->shaders.push_back(
        new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
            "vertexShader.glsl", "fragmentShader.glsl"));
    this->shaders.push_back(
        new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
            "skyBoxVert.glsl", "skyboxFrag.glsl"));
    this->shaders.push_back(
        new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
            "cubeMapVert.glsl", "cubeMapFrag .glsl"));
}

void Game::initTextures()
{
    //TEXTURE INIT
    //Texture 0
    this->textures.push_back(new Texture("Textures/NANI.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/NANI_Specular.png", aiTextureType_SPECULAR));
    //Texture 1
    this->textures.push_back(new Texture("Textures/Shrek_MMH.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/Shrek_MMH_Specular.png", aiTextureType_SPECULAR));
    //Texture _DOOR
    this->textures.push_back(new Texture("Textures/Door.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/door_tex.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/door_tex2.jpg", GL_TEXTURE_2D));
    //Tex_Wall
    this->textures.push_back(new Texture("Textures/wooden_wall.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/paintedWall_Wall.jpg", GL_TEXTURE_2D));
    //Tex_Ceiling
    this->textures.push_back(new Texture("Textures/ceiling_texture.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/tiled_ceiling.jpg", GL_TEXTURE_2D));
    //Tex_Floor
    this->textures.push_back(new Texture("Textures/stone_floor.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/brick_floor.jpg", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/grass_floor.jpg", GL_TEXTURE_2D));
}

void Game::initMaterials()
{
    //MATERIAL 0
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
        0, 1, 1, 1));
}


//Level file reading
int Game::initReadLevelCols(string fileName)
{
    std::ifstream file("CSVFile/FileToRead.csv");
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
    return col;
}

void Game::initReadLevelFile()
{
    this->col = initReadLevelCols(this->fileName);
    std::stringstream ss;
    std::ifstream in_file(this->fileName);
    std::string line = "";

    string objType = "";
    string texNum = " ";
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

            this->ObjType(objType, texNum, posX, posY, posZ);

            objType = "";
            texNum;
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

void Game::ObjType(string objType, string texNum, int posX, int posY, int posZ) {

    if (objType == "PointLight")
    {
        this->pointLights.push_back(new PointLight(glm::vec3(posX, posY, posZ)));
        //    std::cout << "Light Point" << "\n";
        //    break
    }
    else if (objType == "SpotLight") {
        this->spotLights.push_back(new SpotLight(glm::vec3(posX, posY, posZ), glm::vec3(0.f, 90.f, 0.f)));
        //    std::cout << "Light Spot" << "\n";
        //    break;
    }
    else if(objType == "DirectionalLight") {
        this->dirLights.push_back(new DirLight(glm::vec3(posX, posY, posZ), glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f)));
        //    std::cout << "Light Dir" << "\n";
        //    break;
    }
    else {

        string textureString = "Textures/" + texNum;
        const char* beep = textureString.c_str();
        string modelString = "Models/" + objType;

        this->models.push_back(new Model(
            glm::vec3(posX, posY, posZ),
            this->materials[0],
            new Texture(beep, GL_TEXTURE_2D),
            new Texture("Textures/NANI.png", GL_TEXTURE_2D),
            NULL,
            NULL,
            modelString,
            glm::vec3(0.f, 90.f, 0.f)
        )
        );
    }
}


void Game::initModels()
{
    std::vector<Mesh*> meshes;
    std::vector<Mesh*> meshes2;
    this->models.push_back(new Model(
        glm::vec3(0, 0, 0),
        this->materials[0],
        new Texture("backPack/backpack_diffuse.jpg", GL_TEXTURE_2D),
        new Texture("backPack/backpack_specular.jpg", GL_TEXTURE_2D),
        new Texture("backPack/backpack_normal.png", GL_TEXTURE_2D),
        new Texture("backPack/backpack_ao.jpg", GL_TEXTURE_2D),
        "backPack/backpack.obj",
        glm::vec3(0.f, 90.f, 0.f)
    )
    );

    //meshes.push_back(
    //    new Mesh(
    //        &Pyramid(),
    //        glm::vec3(0.f, 0.f, 0.f),
    //        glm::vec3(0.f),
    //        glm::vec3(0.f),
    //        glm::vec3(2.f)
    //    )
    //);

    //meshes2.push_back(
    //    new Mesh(
    //        &Quad(),
    //        glm::vec3(0.f, 0.f, 0.f),
    //        glm::vec3(0.f),
    //        glm::vec3(-90.f, 0.f, 0.f),
    //        glm::vec3(100.f)
    //    )
    //);

    //this->models.push_back(new Model(
    //    glm::vec3(2.f, 0.f, 0.f),
    //    this->materials[0],
    //    this->textures[TEX_NANI],
    //    this->textures[TEX_NANI_SPECULAR],
    //    meshes
    //    )
    //);

    //this->models.push_back(new Model(
    //    glm::vec3(-2.f, 0.f, 0.f),
    //    this->materials[0],
    //    this->textures[TEX_SHREK_MMH1],
    //    this->textures[TEX_SHREK_SPECULAR],
    //    meshes
    //    )
    //);

    //this->models.push_back(new Model(
    //    glm::vec3(2.f, -5.f, 2.f),
    //    this->materials[0],
    //    this->textures[TEX_SHREK_MMH1],
    //    this->textures[TEX_SHREK_SPECULAR],
    //    meshes2
    //)
    //);

#pragma region Pyramids
    meshes.push_back(
        new Mesh(
            &Pyramid(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(2.f)
        )
    );

    this->models.push_back(new Model(
        glm::vec3(-10.f, 0.f, -10.f),
        this->materials[0],
        this->textures[TEX_SHREK],
        this->textures[TEX_SHREK_SPECULAR], NULL, NULL,
        meshes
    )
    );

    this->models.push_back(new Model(
        glm::vec3(10.f, 0.f, -10.f),
        this->materials[0],
        this->textures[TEX_NANI],
        this->textures[TEX_NANI_SPECULAR], NULL, NULL,
        meshes
    )
    );
#pragma endregion

   
//#pragma region LEVEL MODELS
//    this->models.push_back(new Model(
//        glm::vec3(0.f, 1.f, 10.f),
//        this->materials[0],
//        this->textures[TEX_PAINTWALL],
//        this->textures[TEX_NANI_SPECULAR],
//        "Models/GADE7312_WALLS.obj",
//        glm::vec3(0.f, 90.f, 0.f)
//    )
//    );
//
//    //Floor
//    this->models.push_back(new Model(
//        glm::vec3(0.f, 1.f, 10.f),
//        this->materials[0],
//        this->textures[TEX_WALL],
//        this->textures[TEX_NANI_SPECULAR],
//        "Models/GADE7312_FLOOR.obj",
//        glm::vec3(0.f, 90.f, 0.f)
//    )
//    );
//
//    ////Roof
//    //this->models.push_back(new Model(
//    //    glm::vec3(0.f, 14.f, 10.f),
//    //    this->materials[0],
//    //    this->textures[TEX_CEILING],
//    //    this->textures[TEX_NANI_SPECULAR],
//    //    "Models/GADE7312_FLOOR.obj",
//    //    glm::vec3(0.f, 90.f, 0.f)
//    //)
//    //);
//#pragma endregion
//
//#pragma region DOOR MODELS
//    this->models.push_back(new Model(
//        glm::vec3(4.f, 0.f, 82.f),
//        this->materials[0],
//        this->textures[TEX_DOOR],
//        this->textures[TEX_NANI_SPECULAR], NULL, NULL,
//        "Models/GADE7312_Door.obj",
//        glm::vec3(0.f, 90.f, 0.f)
//    )
//    );
//
//    this->models.push_back(new Model(
//        glm::vec3(-36.f, 0.f, 51.f),
//        this->materials[0],
//        this->textures[TEX_DOOR2],
//        this->textures[TEX_NANI_SPECULAR], NULL, NULL,
//        "Models/GADE7312_Door.obj",
//        glm::vec3(0.f, 90.f, 0.f)
//    )
//    );
//
//    this->models.push_back(new Model(
//        glm::vec3(44.f, 0.f, 51.f),
//        this->materials[0],
//        this->textures[TEX_DOOR3],
//        this->textures[TEX_NANI_SPECULAR], NULL, NULL,
//        "Models/GADE7312_Door.obj",
//        glm::vec3(0.f, 90.f, 0.f)
//    )
//    );
//#pragma endregion


    for (auto*& i : meshes)
        delete i;

    for (auto*& i : meshes2)
        delete i;
}

void Game::initLights()
{
    //Directional Lighting
    this->dirLights.push_back(new DirLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.f)));

    //Point Lights
    //this->pointLights.push_back(new PointLight(glm::vec3(1.f)));
    //this->pointLights.push_back(new PointLight(glm::vec3(50.f, 0.f, -50.f)));

    //Spot Lights
    //this->spotLights.push_back(new SpotLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 90.f, 0.f)));
}

void Game::initUniforms()
{
    //INIT UNIFORMS
    //glUseProgram(shaderProgram);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix", false);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix", false);

    for (DirLight* dl : this->dirLights) {
        dl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
    }

    for (size_t i = 0; i < this->pointLights.size(); i++)
    {
        this->pointLights[i]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM], to_string(i));
    }

    for (size_t i = 0; i < this->spotLights.size(); i++)
    {
        this->spotLights[i]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM], to_string(i));
    }
}

unsigned int Game::loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            SOIL_free_image_data(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            SOIL_free_image_data(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


void Game::updateUniforms()
{
    //Update View Matix (camera)
    this->ViewMatrix = this->camera.getViewMatrix();

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

    for (DirLight* dl : this->dirLights) {
        dl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
    }

    for (size_t i = 0; i < this->pointLights.size(); i++)
    {
        this->pointLights[i]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM], to_string(i));
    }

    for (size_t i = 0; i < this->spotLights.size(); i++)
    {
        this->spotLights[i]->sendToShader(*this->shaders[SHADER_CORE_PROGRAM], to_string(i));
    }

    //Update frame buffer size and projection matrix
    glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);


    //ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(glm::radians(fov),
        static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
        this->nearPlane,
        this->farPlane);

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");


}

void Game::updateKeyboardInputs()
{
    //Program
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(this->window, GLFW_TRUE);
        std::cout << "\n=======     Engine Closed       =======\n";
    }

    //Camera
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->camera.move(this->dt, FORWARD);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->camera.move(this->dt, LEFT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->camera.move(this->dt, BACKWARD);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->camera.move(this->dt, RIGHT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        this->camera.move(this->dt, CROUCH);
    }
    else if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
        this->camera.move(this->dt, NOTCROUCH);
    }
    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        this->camera.move(this->dt, JUMP);
    }

    //}
    //if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
    //{
    //    this->camPosition.y += 0.005f;
    //}
    //if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS)
    //{
    //    this->camPosition.y -= 0.005f;
    //}
}

void Game::updateDT()
{
    this->curTime = static_cast<float>(glfwGetTime());
    this->dt = this->curTime - this->lastTime;
    this->lastTime = this->curTime;
}

void Game::updateMouseInputs()
{
    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    if (this->firstMouse)
    {
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }

    //Calc Offset
    this->mouseOffsetX = this->mouseX - this->lastMouseX;
    this->mouseOffsetY = this->mouseY - this->lastMouseY;

    //Set last x and y
    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;

    //Move Light
    //if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    //{
    //    this->pointLights[0]->setPosition(this->camera.getPosition());
    //}
}

void Game::updateInput()
{
    glfwPollEvents();

    this->updateKeyboardInputs();
    this->updateMouseInputs();

    this->camera.updateInput(dt, -1, this->mouseOffsetX, this->mouseOffsetY);
}


//Constructors / Destructors
Game::Game(const char* title, const int WINDOW_WIDTH,
    const int WINDOW_HEIGHT, const int GL_VERSION_MAJOR,
    const int GL_VERSION_MINOR, bool resizeable, string fileName)

    :
    WINDOW_WIDTH(WINDOW_WIDTH),
    WINDOW_HEIGHT(WINDOW_HEIGHT),
    GL_VERSION_MAJOR(GL_VERSION_MAJOR),
    GL_VERSION_MINOR(GL_VERSION_MINOR),
    camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
    //Init variables
    this->window = nullptr;
    this->frameBufferHeight = this->WINDOW_HEIGHT;
    this->frameBufferWidth = this->WINDOW_WIDTH;

    //INIT MATRICES
    this->camPosition = glm::vec3(0.f, 0.f, 2.f);
    this->worldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3(0.f, 0.f, -1.f);

    this->fov = 90.f;
    this->nearPlane = 0.1f;
    this->farPlane = 1000.f;

    this->dt = 0.f;
    this->curTime = 0.f;
    this->lastTime = 0.f;

    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;

    //FOR FPS COUNTER
    this->previousTime = 0;
    this->frameCount = 0;
    wantFPS = false;

    this->fileName = fileName;

    this->initGLFW();
    this->initWindow(title, resizeable);
    this->initGLAD();
    this->initOpenGLOptions();

    this->initMatricies();
    this->initShaders();

    // cube VAO
    glGenVertexArrays(1, &this->cubeVAO);
    glGenBuffers(1, &this->cubeVBO);
    glBindVertexArray(this->cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &this->skyboxVAO);
    glGenBuffers(1, &this->skyboxVBO);
    glBindVertexArray(this->skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    this->cubemapTexture = loadCubemap(faces);

    this->shaders[cubeMapShader]->use();
    this->shaders[cubeMapShader]->set1i(0, "skybox");

    this->shaders[skyBoxShader]->use();
    this->shaders[skyBoxShader]->set1i(0, "skybox");

    this->initTextures();
    this->initMaterials();
    this->initReadLevelFile();
    //this->initModels();

    //this->initLights();
    this->initUniforms();
}

Game::~Game() {
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++)
        delete this->shaders[i];

    for (size_t i = 0; i < this->textures.size(); i++)
        delete this->textures[i];

    for (size_t i = 0; i < this->materials.size(); i++)
        delete this->materials[i];

    for (auto*& i : this->models)
        delete i;

    for (size_t i = 0; i < this->pointLights.size(); i++)
        delete this->pointLights[i];

    glDeleteVertexArrays(1, &this->cubeVAO);
    glDeleteVertexArrays(1, &this->skyboxVAO);
    glDeleteBuffers(1, &this->cubeVBO);
    glDeleteBuffers(1, &this->skyboxVAO);
}


//Accessor
int Game::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

//Modifiers
void Game::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}


//Functions
void Game::update()
{
    glViewport(0, 0, this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    this->render();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glfwPollEvents();
    this->updateInput();
    this->updateDT();
    if (wantFPS)
    {
        this->fpsCounter();
    }    
}

void Game::render()
{
    //UPDATE ---


    //DRAW ---
    //Clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Update the game uniforms
    this->updateUniforms();

    //Render Models
    for (auto& i : this->models) {
        i->render(this->shaders[SHADER_CORE_PROGRAM]);
    }

    this->shaders[SHADER_CORE_PROGRAM]->set1i(this->nearPlane, "near_plane");
    this->shaders[SHADER_CORE_PROGRAM]->set1i(this->farPlane, "far_plane");

    // draw scene as normal
    this->shaders[cubeMapShader]->use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = this->camera.getViewMatrix();
    glm::mat4 projection = this->ProjectionMatrix;
    this->shaders[cubeMapShader]->setMat4fv(model, "model");
    this->shaders[cubeMapShader]->setMat4fv(this->ViewMatrix, "view");
    this->shaders[cubeMapShader]->setMat4fv(this->ProjectionMatrix, "projection");
    this->shaders[cubeMapShader]->setVec3f(this->camera.getPosition(), "cameraPos");
    // cubes
    this->shaders[cubeMapShader]->use();
    glBindVertexArray(this->cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    this->shaders[skyBoxShader]->use();
    view = glm::mat4(glm::mat3(this->camera.getViewMatrix())); // remove translation from the view matrix
    this->shaders[skyBoxShader]->setMat4fv(view, "view");
    this->shaders[skyBoxShader]->setMat4fv(projection, "projection");
    // skybox cube
    this->shaders[skyBoxShader]->use();
    glBindVertexArray(this->skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default

    //End Draw
    glfwSwapBuffers(window);
    glFlush();


    //Security, backup to unbind
    glBindVertexArray(0);
    glUseProgram(0);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::fpsCounter() {
    double currentTime = glfwGetTime();
    frameCount++;
    // If a second has passed.
    if (currentTime - previousTime >= 1.0)
    {
        // Display the frame count here any way you want.
        printf("%f ms/frame\n", 1000.0 / double(this->frameCount));

        frameCount = 0;
        previousTime = currentTime;
    }
}

void Game::userCommands()
{
    if (glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        string temp;
        cout << "Type 'help' to see a list of possible commands";
        cout << "Enter a command:\n ";
        cin >> temp;

        if (temp == "help")
        {
            cout << "Possible Commands: fps, triangles, loadlevel, spawnmodel \n";
            cout << "Press Enter while in game engine to access console commands again \n";
            return;
        }
        else if (temp == "fps") {
            if (wantFPS == false)
            {
                wantFPS = true;
                cout << "FPS counter Enabled \n";
                return;
            }
            else {
                wantFPS = false;
                cout << "FPS counter Disabled \n";
                return;
            }
        }
        else if (temp == "triangles") {
            int tempNum = 0;
            for (size_t i = 0; i < this->models.size(); i++)
            {
                for (Mesh* mesh : this->models[i]->meshes) {
                    tempNum += mesh->nrOfVertices;
                }
            }

            int numOfTriangles = 0;
            numOfTriangles = (tempNum * 2);
            std::cout << "Nr of Triangles: " << numOfTriangles << "\n";
            
        }
        else if (temp == "loadlevel") {
            bool loadGOODhere = false;
            cout << "What level would you like to load? Type END to exit this \n";
            string levelName;
            cin >> levelName;

            while (loadGOODhere == false)
            {
                if (levelName == "END")
                {
                    cout << "\n BACK TO GAME! \n";
                    return;
                }
                else
                {
                    levelName = "CSVFile/" + levelName;
                    ifstream input_file(levelName);
                    if (!input_file.is_open())
                    {
                        cout << "FILE NOT FOUND! \n";
                        cout << "What level would you like to load? Type END to exit this \n";
                        cin >> levelName;
                    }
                    else {
                        loadGOODhere = true;
                        input_file.close();
                    }
                }
            }

            this->fileName = levelName;
            this->models.clear();
            this->initReadLevelFile();
            cout << "Level Loaded \n";
        }
        else if (temp == "spawnmodel") {
            bool loadGOODhere = false;

            string fileName;
            float xPos, yPos, zPos;
            float xRot, yRot, zRot;
            cout << "Please enter file Name, include file type extension in the name. Type END to exit this \n ";
            cin >> fileName;
            fileName = "Models/" + fileName;

            while (loadGOODhere == false) {
                if (fileName == "END")
                {
                    cout << "\n BACK TO GAME! \n";
                    return;
                }
                else {
                    fileName = "Models/" + fileName;
                    ifstream input_file(fileName);
                    if (!input_file.is_open())
                    {
                        cout << "FILE NOT FOUND! \n";
                        cout << "What model would you like to load? Type END to exit this \n";
                        cin >> fileName;
                    }
                    else {
                        loadGOODhere = true;
                        input_file.close();
                    }
                }
            }

            cout << "Please enter X Position \n ";
            cin >> xPos;
            cout << "Please enter Y Position \n ";
            cin >> yPos;
            cout << "Please enter Z Position \n ";
            cin >> zPos;

            this->models.push_back(new Model(
                glm::vec3(xPos, yPos, zPos),
                this->materials[0],
                this->textures[TEX_PAINTWALL],
                this->textures[TEX_NANI_SPECULAR],
                NULL,
                NULL,
                fileName,
                glm::vec3(0.f, 90.f, 0.f)
            )
            );
            cout << "Model Loaded \n ";
            return;
        }
        else {
            cout << "Incorrect Command, please return to game engine window and press enter to open command prompt\n ";
            cout << "Press Enter while in game engine to access console commands again \n";
            return;
        }
    }
}


//Static Functions
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
}
