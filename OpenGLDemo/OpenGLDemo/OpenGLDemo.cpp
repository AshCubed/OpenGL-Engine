// OpenGLDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"libs.h"
using namespace std;

//float vertices[] = {
//            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
//             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
//             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
//};

Vertex vertices[] =
{
    //Position
    glm::vec3(0.0f, 0.5f, 0.f),         glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),
    glm::vec3(-0.5f, -0.5f, 0.f),       glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),
    glm::vec3(0.5f, -0.5f, 0.f),        glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f)
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indicies[] =
{
    0, 1, 2
};

void updateInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool loadShaders(GLuint& program) {
    bool loadSuccess = true;
    char infoLog[512];
    GLint success;

    string temp = "";
    string src = "";

    ifstream in_file;

    //VertexShader
    #pragma region VertexShaderCode
    in_file.open("vertexShader.glsl");

    if (in_file.is_open())
    {
        while (getline(in_file, temp)) {
            src += temp + "\n";
        }
    }
    else {
        cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    unsigned int vertexShader;
    const GLchar* vertexShaderSource = src.c_str();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::LOADSHADDERS::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
        cout << infoLog << "\n";
        loadSuccess = false;
    }

    temp = "";
    src = "";
#pragma endregion

    //FragmentShader
    #pragma region FragmentShaderCode
    in_file.open("fragmentShader.glsl");

    if (in_file.is_open())
    {
        while (getline(in_file, temp)) {
            src += temp + "\n";
        }
    }
    else {
        cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << "\n";
        loadSuccess = false;
    }

    in_file.close();

    unsigned int fragmentShader;
    const GLchar* fragmentShaderSource = src.c_str();
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::LOADSHADDERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << "\n";
        cout << infoLog << "\n";
        loadSuccess = false;
    }

    temp = "";
    src = "";
#pragma endregion

    //Program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "ERROR::LOADSHADDERS::COULD_NOT_LINK_PROGRAM" << "\n";
        cout << infoLog << "\n";
        loadSuccess = false;
    }

    //End
    glUseProgram(0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return loadSuccess;
}

int main(void)
{
    //INIT GLFW
    glfwInit();

    //Create Window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hi Ashveer", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to creste GLFW window" << endl;
        glfwTerminate();
        return -1;

    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    //OPENGL OPTIONS
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //SHADER INIT
    //loadShaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    if (loadShaders(shaderProgram) == false)
    {
        glfwTerminate();
    }

    //MODEL

    //VAO, VBO, EBO
    //GEN VAO and BIND
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //GEN VBO AND BIND AND SEND DATA
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //GEN EBO AND BIND AND SEND DATA
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    //SET VERTEX POINTERS AND ENABLE (INPUT ASSEMVLY)
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    //Texcoord
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    //BIND VAO 0
    glBindVertexArray(0);


    //MAIN LOOP
    while (!glfwWindowShouldClose(window))
    {
        //UDATE INPUT
        glfwPollEvents();

        //UPDATE ---
        updateInput(window);

        //DRAW ---
        //Clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //USE PROGRAM
        glUseProgram(shaderProgram);

        //Bind Vertex Array object
        glBindVertexArray(VAO);

        //Draw
        glDrawElements(GL_TRIANGLES, nrOfVertices, GL_UNSIGNED_INT, 0);

        //End Draw
        glfwSwapBuffers(window);
        glfwPollEvents();
        glFlush();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
