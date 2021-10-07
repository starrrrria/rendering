#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h> //目录下的档案
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <assert.h>
#include <AntTweakBar.h>
#include "stdio.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>

#define GLUT_DISABLE_ATEXIT_HACK
#include <math.h>
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
using namespace::glm;

//Model Data
float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
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

vec3 cubePositions[] = {
    vec3(1.0f,-5.5f,-3.0f),//Phong
    vec3(-1.0f,-5.5f,-3.0f), //Toon
    vec3(3.0f,-5.5f,-3.0f), //Phong
    vec3(5.0f,-5.5f,-3.0f),//Oren
    vec3(7.0f,-5.5f,-3.0f)
};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(vec3(-0.5f,5.0f,1.0f),radians(-30.0f),radians(180.0f),vec3(0,1.0f,0));

float lastX;
float lastY;
float Angle = 0;
void update(){
    float lastTime = 0;
    float currTime = (float)glfwGetTime();
    float  delta = (currTime - lastTime) * 0.001f;
    if (delta > 0.03f){
        delta = 0.03f;
        lastTime = currTime;
        Angle += 0.2f;
    }
    
}
bool firstMouse = true;

unsigned int LoadImageToGPU(const char* filename,GLint internalFormat, GLenum format,int textureSlot){
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer); //产生buffer
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);
    
    int width,height,nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename,&width,&height,&nrChannel,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } //第几登记mipmap,不给边缘
    else{
        printf("load image failed.");
    }
    stbi_image_free(data);
    return TexBuffer;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.speedZ = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.speedZ = -1.0f;
    }
    else{
        camera.speedZ = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.speedX = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.speedX = -1.0f;
    }
    else{
        camera.speedX = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.speedY = -1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.speedY = 1.0f;
    }
    else{
        camera.speedY = 0;
    }
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float deltaX,deltaY;
    deltaX = xpos - lastX;
    deltaY = ypos - lastY;
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(deltaX, deltaY);
}
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, const char * argv[]) {
    std::string exePath = argv[0];
    //std::cout << exePath.substr(0,exePath.find_last_of('/'))+ '/Structure/Structure/Wall-Window.obj' << std::endl;
    //Open window
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //终止
        return -1;
    }
    glfwMakeContextCurrent(window); //绑定使用
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
    glfwSetCursorPosCallback(window, mouse_callback);
    
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glCullFace(GL_BACK);
    
    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW fault");
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, 800, 600); //设置窗口大小起始坐标终止坐标
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    Shader* cubeShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/rendering/vertexSource.vert","/Users/buxin/Documents/real-time-rendering/rendering/rendering/fragementSource.frag");
    Shader* cubeShaderToon = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/rendering/vertexSource.vert","/Users/buxin/Documents/real-time-rendering/rendering/rendering/ToonFragement.frag");
    Shader* cubeShaderOren = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/rendering/vertexSource.vert","/Users/buxin/Documents/real-time-rendering/rendering/rendering/OrenFragment.frag");
    Material* cubeMaterial = new Material(cubeShader,
                                        LoadImageToGPU("/Users/buxin/Documents/real-time-rendering/rendering/rendering/container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
                                        LoadImageToGPU("/Users/buxin/Documents/real-time-rendering/rendering/rendering/container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
                                        vec3 (1.0f,1.0f,1.0f),
                                          64.0f);
    
    mat4 modelMat = mat4(1.0f);
    mat4 modelMatToon = mat4(1.0f);
    mat4 modelMatOren = mat4(1.0f);
    mat4 viewMat = mat4(1.0f);
    mat4 projMat = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 *sizeof(float)));
    glEnableVertexAttribArray(1);
    
    unsigned int TexBufferA;
    unsigned int TexBufferB;
    TexBufferA = LoadImageToGPU("/Users/buxin/Documents/real-time-rendering/rendering/rendering/container2.png", GL_RGBA, GL_RGBA, 0);
    TexBufferB = LoadImageToGPU("/Users/buxin/Documents/real-time-rendering/rendering/rendering/container2_specular.png", GL_RGBA, GL_RGBA, 0);
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //Process input
        processInput(window); //下一帧输入
        //Clear screen
        glClearColor(0.8f,0.8f,0.8f,1.0f); //r,g,b,
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        viewMat = camera.GetfirstViewMatrix();
        
//Phong model
        modelMat = translate(mat4(1.0f), cubePositions[0]);
        modelMat = rotate(modelMat, radians(-45.0f), vec3(0.0f,1.0f,1.0f));
        modelMat = rotate(modelMat, (float)glfwGetTime(), vec3(0.5f, 0.0f, 0.5f));
        cubeShader -> use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID,"modelMat"),1,GL_FALSE,value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(cubeShader->ID,"objColor"),1.0f,0.5f,0.31f);
        glUniform3f(glGetUniformLocation(cubeShader->ID,"ambientColor"),0.4f,0.4f,0.4);//环境光
        glUniform3f(glGetUniformLocation(cubeShader->ID,"lightPos"), 1.5f,-4.5f, -3.0f);
        glUniform3f(glGetUniformLocation(cubeShader->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(cubeShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1i(glGetUniformLocation(cubeShader->ID,"ourTexture"),0);
        glUniform1f(glGetUniformLocation(cubeShader->ID,"specNum"),32.0f);
//        cubeMaterial->shader->SetUniform3f("material.ambient", cubeMaterial->ambient);
//        cubeMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
//        cubeMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
//        cubeMaterial->shader->SetUniform1f("material.shininess", cubeMaterial->shininess);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        modelMat = translate(mat4(1.0f), cubePositions[2]);
        modelMat = rotate(modelMat, radians(-45.0f), vec3(0.0f,1.0f,1.0f));
        modelMat = rotate(modelMat, (float)glfwGetTime(), vec3(0.5f, 0.0f, 0.5f));
        cubeShader -> use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID,"modelMat"),1,GL_FALSE,value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(cubeShader->ID,"objColor"),1.0f,0.5f,0.31f);
        glUniform3f(glGetUniformLocation(cubeShader->ID,"ambientColor"),0.4f,0.4f,0.4);//环境光
        glUniform3f(glGetUniformLocation(cubeShader->ID,"lightPos"), 3.5f,-4.5f, -3.0f);
        glUniform3f(glGetUniformLocation(cubeShader->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(cubeShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1i(glGetUniformLocation(cubeShader->ID,"ourTexture"),0);
        glUniform1f(glGetUniformLocation(cubeShader->ID,"specNum"),8.0f);
//        cubeMaterial->shader->SetUniform3f("material.ambient", cubeMaterial->ambient);
//        cubeMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
//        cubeMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
//        cubeMaterial->shader->SetUniform1f("material.shininess", cubeMaterial->shininess);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
//Toon model
        modelMatToon = translate(mat4(1.0f), cubePositions[1]);
        modelMatToon = rotate(modelMatToon, radians(-45.0f), vec3(0.0f,1.0f,1.0f));
        modelMatToon = rotate(modelMatToon, (float)glfwGetTime(), vec3(0.5f, 0.0f, 0.5f));
        cubeShaderToon -> use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderToon->ID,"modelMat"),1,GL_FALSE,value_ptr(modelMatToon));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderToon->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderToon->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(cubeShaderToon->ID,"objColor"),1.0f,0.5f,0.31f);
        glUniform3f(glGetUniformLocation(cubeShaderToon->ID,"lightPos"), -0.6f,-4.5f,-2.8f);
        glUniform3f(glGetUniformLocation(cubeShaderToon->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(cubeShaderToon->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1i(glGetUniformLocation(cubeShaderToon->ID,"ourTexture"),0);
    
//        cubeMaterial->shader->SetUniform3f("material.ambient", cubeMaterial->ambient);
//        cubeMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
//        cubeMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
//        cubeMaterial->shader->SetUniform1f("material.shininess", cubeMaterial->shininess);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
//Oren-nayar model
        modelMatOren = translate(mat4(1.0f), cubePositions[3]);
        modelMatOren = rotate(modelMatOren, radians(-45.0f), vec3(0.0f,1.0f,1.0f));
        modelMatOren = rotate(modelMatOren, (float)glfwGetTime(), vec3(0.5f, 0.0f, 0.5f));
        cubeShaderOren -> use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderOren->ID,"modelMat"),1,GL_FALSE,value_ptr(modelMatOren));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderOren->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderOren->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"objColor"),1.0f,0.5f,0.31f);
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"lightPos"), 5.5f,-4.5f, -3.0f);
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1i(glGetUniformLocation(cubeShaderOren->ID,"ourTexture"),0);
        glUniform1f(glGetUniformLocation(cubeShaderOren->ID,"roughness"),0.1f);

//        cubeMaterial->shader->SetUniform3f("material.ambient", cubeMaterial->ambient);
//        cubeMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
//        cubeMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
//        cubeMaterial->shader->SetUniform1f("material.shininess", cubeMaterial->shininess);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        modelMatOren = translate(mat4(1.0f), cubePositions[4]);
        modelMatOren = rotate(modelMatOren, radians(-45.0f), vec3(0.0f,1.0f,1.0f));
        modelMatOren = rotate(modelMatOren, (float)glfwGetTime(), vec3(0.5f, 0.0f, 0.5f));
        cubeShaderOren -> use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBufferA);
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderOren->ID,"modelMat"),1,GL_FALSE,value_ptr(modelMatOren));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderOren->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(cubeShaderOren->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"objColor"),1.0f,0.5f,0.31f);
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"lightPos"), 7.5f,-4.5f, -3.0f);
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(cubeShaderOren->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1i(glGetUniformLocation(cubeShaderOren->ID,"ourTexture"),0);
        glUniform1f(glGetUniformLocation(cubeShaderOren->ID,"roughness"),0.8f);

//        cubeMaterial->shader->SetUniform3f("material.ambient", cubeMaterial->ambient);
//        cubeMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
//        cubeMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
//        cubeMaterial->shader->SetUniform1f("material.shininess", cubeMaterial->shininess);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //Clean up,prepare for next render loop
        glfwSwapBuffers(window); //切换前后buffer
        glfwPollEvents();
        camera.UpdateCameraPos();
    }
    //Exit Program
    glfwTerminate();
    return 0;
}
