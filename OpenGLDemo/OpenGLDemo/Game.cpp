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

    glEnable(GL_CULL_FACE);
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
    this->textures.push_back(new Texture("C:/Users/ashju/Desktop/NANI.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("C:/Users/ashju/Desktop/NANI_Specular.png", GL_TEXTURE_2D));
    //Texture 1
    this->textures.push_back(new Texture("C:/Users/ashju/Desktop/Shrek_MMH.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("C:/Users/ashju/Desktop/Shrek_MMH_Specular.png", GL_TEXTURE_2D));

}

void Game::initMaterials()
{
    //MATERIAL 0
    this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f),
        0, 1));
}

void Game::initModels()
{
    std::vector<Mesh*> meshes;
    std::vector<Mesh*> meshes2;

    meshes.push_back(
        new Mesh(
            &Pyramid(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(2.f)
        )
    );

    meshes2.push_back(
        new Mesh(
            &Quad(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(-90.f, 0.f, 0.f),
            glm::vec3(100.f)
        )
    );

    this->models.push_back(new Model(
        glm::vec3(2.f, 0.f, 0.f),
        this->materials[0],
        this->textures[TEX_NANI],
        this->textures[TEX_NANI_SPECULAR],
        meshes
        )
    );

    this->models.push_back(new Model(
        glm::vec3(-2.f, 0.f, 0.f),
        this->materials[0],
        this->textures[TEX_SHREK_MMH1],
        this->textures[TEX_SHREK_SPECULAR],
        meshes
        )
    );

    this->models.push_back(new Model(
        glm::vec3(2.f, -5.f, 2.f),
        this->materials[0],
        this->textures[TEX_SHREK_MMH1],
        this->textures[TEX_SHREK_SPECULAR],
        meshes2
    )
    );

    this->models.push_back(new Model(
        glm::vec3(0.f, 0.f, 0.f),
        this->materials[0],
        this->textures[TEX_NANI],
        this->textures[TEX_NANI_SPECULAR],
        "C:/Users/ashju/Desktop/untitled.obj"
    )
    );

    for (auto*& i : meshes)
        delete i;

    for (auto*& i : meshes2)
        delete i;
}

void Game::initPointLights()
{
    this->pointLights.push_back(new PointLight(glm::vec3(0.f)));
}

void Game::initLights()
{
    this->initPointLights();
}

void Game::initUniforms()
{
    //INIT UNIFORMS
    //glUseProgram(shaderProgram);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix", false);
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix", false);

    for(PointLight * pl : this->pointLights) {
        pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
    }
}

void Game::updateUniforms()
{
    //Update View Matix (camera)
    this->ViewMatrix = this->camera.getViewMatrix();

    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

    for (PointLight* pl : this->pointLights) {
        pl->sendToShader(*this->shaders[SHADER_CORE_PROGRAM]);
    }

    //Update uniforms
    //this->shaders[SHADER_CORE_PROGRAM]->set1i(0, "texture0");
    //this->shaders[SHADER_CORE_PROGRAM]->set1i(1, "texture1");

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
    if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        this->camPosition.y += 0.005f;
    }
    if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS)
    {
        this->camPosition.y -= 0.005f;
    }
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


    this->initGLFW();
    this->initWindow(title, resizeable);
    this->initGLAD();
    this->initOpenGLOptions();

    this->initMatricies();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
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

    //for (auto*& i : this->meshes)
    //    delete i;
    
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

    /*this->models[0]->rotate(glm::vec3(0.f, 0.01f, 0.f));
    this->models[1]->rotate(glm::vec3(0.f, 0.01f, 0.f));*/
}

void Game::render()
{
    //UPDATE ---


    //DRAW ---
    //Clear
    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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


//Static Functions
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    
    glViewport(0, 0, width, height);
}
