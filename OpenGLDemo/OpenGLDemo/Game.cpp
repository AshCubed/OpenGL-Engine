#include "Game.h"

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
}

void Game::initTextures()
{
    //TEXTURE INIT
    //Texture 0
    this->textures.push_back(new Texture("Textures/NANI.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/NANI_Specular.png", GL_TEXTURE_2D));
    //Texture 1
    this->textures.push_back(new Texture("Textures/Shrek_MMH.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("Textures/Shrek_MMH_Specular.png", GL_TEXTURE_2D));
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
        0, 1));
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
    this->col = initReadLevelCols("CSVFile/FileToRead.csv");
    std::stringstream ss;
    std::ifstream in_file("CSVFile/FileToRead.csv");
    std::string line = "";

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

            this->ObjType(objType, texNum, posX, posY, posZ);

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

void Game::ObjType(int objType, int texNum, int posX, int posY, int posZ) {
    switch (objType) {
    case 1:
        this->models.push_back(new Model(
            glm::vec3(posX, posY, posZ),
            this->materials[0],
            this->textures[ObjTex(texNum)],
            this->textures[TEX_NANI_SPECULAR],
            "Models/GADE7312_WALLS.obj",
            glm::vec3(0.f, 90.f, 0.f)
        )
        );
        std::cout << "Model Created: walls" << "\n";
        break;
    case 2:
        this->models.push_back(new Model(
            glm::vec3(posX, posY, posZ),
            this->materials[0],
            this->textures[ObjTex(texNum)],
            this->textures[TEX_NANI_SPECULAR],
            "Models/GADE7312_FLOOR.obj",
            glm::vec3(0.f, 90.f, 0.f)
        )
        );
        std::cout << "Model Created: Floor" << "\n";
        break;
    case 3:
        this->models.push_back(new Model(
            glm::vec3(posX, posY, posZ),
            this->materials[0],
            this->textures[ObjTex(texNum)],
            this->textures[TEX_NANI_SPECULAR],
            "Models/GADE7312_Door.obj",
            glm::vec3(0.f, 90.f, 0.f)
        )
        );
        std::cout << "Model Created: Door" << "\n";
        break;
    case 4:
        this->spotLights.push_back(new SpotLight(glm::vec3(posX, posY, posZ), glm::vec3(0.f, 90.f, 0.f)));
        std::cout << "Light Spot" << "\n";
        break;
    case 5:
        this->dirLights.push_back(new DirLight(glm::vec3(posX, posY, posZ), glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f)));
        std::cout << "Light Dir" << "\n";
        break;
    case 6:
        this->pointLights.push_back(new PointLight(glm::vec3(posX, posY, posZ)));
        std::cout << "Light Point" << "\n";
        break;
    }
}

texture_enum Game::ObjTex(int num) {
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


void Game::initModels()
{
    std::vector<Mesh*> meshes;
    std::vector<Mesh*> meshes2;

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
        this->textures[TEX_SHREK_SPECULAR],
        meshes
    )
    );

    this->models.push_back(new Model(
        glm::vec3(10.f, 0.f, -10.f),
        this->materials[0],
        this->textures[TEX_NANI],
        this->textures[TEX_NANI_SPECULAR],
        meshes
    )
    );
#pragma endregion

#pragma region LEVEL MODELS
    this->models.push_back(new Model(
        glm::vec3(0.f, 1.f, 10.f),
        this->materials[0],
        this->textures[TEX_PAINTWALL],
        this->textures[TEX_NANI_SPECULAR],
        "Models/GADE7312_WALLS.obj",
        glm::vec3(0.f, 90.f, 0.f)
    )
    );

    //Floor
    this->models.push_back(new Model(
        glm::vec3(0.f, 1.f, 10.f),
        this->materials[0],
        this->textures[TEX_WALL],
        this->textures[TEX_NANI_SPECULAR],
        "Models/GADE7312_FLOOR.obj",
        glm::vec3(0.f, 90.f, 0.f)
    )
    );

    ////Roof
    //this->models.push_back(new Model(
    //    glm::vec3(0.f, 14.f, 10.f),
    //    this->materials[0],
    //    this->textures[TEX_CEILING],
    //    this->textures[TEX_NANI_SPECULAR],
    //    "Models/GADE7312_FLOOR.obj",
    //    glm::vec3(0.f, 90.f, 0.f)
    //)
    //);
#pragma endregion

#pragma region DOOR MODELS
    this->models.push_back(new Model(
        glm::vec3(4.f, 0.f, 82.f),
        this->materials[0],
        this->textures[TEX_DOOR],
        this->textures[TEX_NANI_SPECULAR],
        "Models/GADE7312_Door.obj",
        glm::vec3(0.f, 90.f, 0.f)
    )
    );

    this->models.push_back(new Model(
        glm::vec3(-36.f, 0.f, 51.f),
        this->materials[0],
        this->textures[TEX_DOOR2],
        this->textures[TEX_NANI_SPECULAR],
        "Models/GADE7312_Door.obj",
        glm::vec3(0.f, 90.f, 0.f)
    )
    );

    this->models.push_back(new Model(
        glm::vec3(44.f, 0.f, 51.f),
        this->materials[0],
        this->textures[TEX_DOOR3],
        this->textures[TEX_NANI_SPECULAR],
        "Models/GADE7312_Door.obj",
        glm::vec3(0.f, 90.f, 0.f)
    )
    );
#pragma endregion


    for (auto*& i : meshes)
        delete i;

    for (auto*& i : meshes2)
        delete i;
}

void Game::initLights()
{
    //Directional Lighting
    this->dirLights.push_back(new DirLight(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f)));

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
        cout << "\n=======     Engine Closed       =======\n";
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
    if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        this->pointLights[0]->setPosition(this->camera.getPosition());
    }
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
    const int GL_VERSION_MINOR, bool resizeable)

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

    this->initGLFW();
    this->initWindow(title, resizeable);
    this->initGLAD();
    this->initOpenGLOptions();

    this->initMatricies();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    //this->initReadLevelFile();
    this->initModels();
    this->initLights();
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
    glfwPollEvents();
    this->updateInput();
    this->updateDT();
    if (wantFPS)
    {
        this->fpsCounter();
    }
   /* this->models[0]->updateRotation(glm::vec3(0.f, 0.01f, 0.f));
    this->models[1]->updateRotation(glm::vec3(0.f, 0.01f, 0.f));*/
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
        cout << "Enter a command:\n ";
        cin >> temp;

        if (temp == "help")
        {
            cout << "Possible Commands: fps, triangles, load level, spawn model \n";
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

        }
        else if (temp == "loadlevel") {

        }
        else if (temp == "spawnmodel") {
            string fileName;
            float xPos, yPos, zPos;
            float xRot, yRot, zRot;
            cout << "Please enter file Name, include file type extension in the name \n ";
            cin >> fileName;
            fileName = "Models/" + fileName;
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
                fileName,
                glm::vec3(0.f, 90.f, 0.f)
            )
            );
            cout << "Model Loaded \n ";
            return;
        }
        else {
            cout << "Incorrect Command, please return to game engine window and press enter to open command prompt\n ";
            return;
        }
    }
}


//Static Functions
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    
    glViewport(0, 0, width, height);
}
