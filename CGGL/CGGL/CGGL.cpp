#undef GLFW_DLL
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>

#include "Shader.h"
#include "Window.h"
#include "Mesh.h"

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

float triOffset = 0.0f;
float triIncrement = 0.0005f;
float triMaxOffset = 1.8f;
float swing = 0.0f;
bool endgame_background = false;

bool direction = true;

//Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateSnack()
{
    GLfloat vertices[] =
    {
         .750f, .750f, .0f,
        .750f, .0f, .0f,
        .55f, .0f, .0f,
        .55f, .65f, .0f,
        
    };

    unsigned int indices[] =
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void CreatePackage()
{
    GLfloat vertices[] =
    {

        -0.7f, 1.0f, 0.0f,
        0.7f,  1.0f, 0.0f,
        0.2f,  0.0f, 0.0f,
        -0.2f, 0.0f, 0.0f,

    };

    unsigned int indices[] =
    {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
}

void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main()
{
    mainWindow = Window(WIDTH, HEIGHT);
    mainWindow.initialise();

    CreateSnack();
    CreateSnack();
    CreatePackage();
    CreateShaders();

    GLuint uniformModel = 0, uniformProjection = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    //Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        //Get + Handle user input events
        glfwPollEvents();
        
        if (direction) { 
            swing += 0.0005f;
            triOffset += triIncrement; }

        if (abs(triOffset) >= triMaxOffset) { 
            swing = 0.0f;
            triOffset = 0.0f;
            endgame_background = !endgame_background;

             }

        //Clear window
        if (endgame_background) {
            glClearColor(0.6f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else{
            glClearColor(0.6f, 0.5f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
       

        //draw here
        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();

        //Object 1
        glm::mat4 model(1.0f);
        
        model = glm::translate(model, glm::vec3(0.3f, -triOffset+0.5f, -2.5f));
        model = glm::rotate(model, swing, glm::vec3(0.3f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.5f, 1.0f, -2.5f));
        
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        //Object 2
        model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(-0.6f, 0.21f, -2.5f));
        model = glm::rotate(model, 0.6f, glm::vec3(0.1f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.6f, 1.5f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        //Object 3
        model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(-0.3f, 0.0f, -2.5f));
        model = glm::rotate(model, 0.6f, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.5f, 1.5f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[2]->RenderMesh();

        //Object 4
        model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, .25f, -2.5f));
        model = glm::rotate(model, 0.6f, glm::vec3(0.2f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.5f, 1.5f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[3]->RenderMesh();

        //Object 5
        model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3( 0, -0.5, -2.5f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[4]->RenderMesh();

       
        

        glUseProgram(0);
        //end draw

        mainWindow.swapBuffers();
    }

    return 0;
}
