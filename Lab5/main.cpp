
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
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
using namespace::glm;


float clickPointX;
float clickPointY;
bool isclick = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float ScaleX = 0.0f;
float ScaleY = 0.0f;
float SplitX = 0.0f;
float SplitY = 0.0f;
float TranslationX = 0.0f;
float TranslationY = 0.0f;
float SquareN = 0.0f;
float SquareScale = 0.0f;
float RotationX = 0.0f;
float RotationY = 0.0f;
float RotationZ = 0.0f;
float xOffset;
float yOffset;

Camera camera(vec3(0,0,3.0f),radians(15.0f),radians(180.0f),vec3(0,1.0f,0));

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
inline void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
{    TwMouseMotion(int(xpos), int(ypos));
    clickPointX = xpos;
    clickPointY = ypos;
    xOffset = xpos;
    yOffset = ypos;
}
inline void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
{   TwEventMouseButtonGLFW(button, action);
    if(action == GLFW_PRESS) switch (button){
        case GLFW_MOUSE_BUTTON_LEFT:
            glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
            
//            clickPointX = (-1) + (clickPointX/SCR_WIDTH) * 2;
//            clickPointY = 1 - (clickPointY/SCR_HEIGHT) * 2;
//            printf("mouse coordinates are %f,%f\n",xOffset,yOffset);
            isclick = false;
            break;
    }
}
inline void TwWindowSizeGLFW3(GLFWwindow* window, int width, int height)
{TwWindowSize(width, height);}
inline void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
{TwEventMouseWheelGLFW(yoffset);}
inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods)
{   TwEventKeyGLFW(key, action);
}
inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint)
{TwEventCharGLFW(codepoint, GLFW_PRESS);}
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void processInput(GLFWwindow *window)
{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        camera.speedZ = 1.0f;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        camera.speedZ = -1.0f;
//    }
//    else{
//        camera.speedZ = 0;
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        camera.speedX = 1.0f;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        camera.speedX = -1.0f;
//    }
//    else{
//        camera.speedX = 0;
//    }
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        camera.speedY = -1.0f;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        camera.speedY = 1.0f;
//    }
//    else{
//        camera.speedY = 0;
//    }
}
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float deltaX,deltaY;
//    deltaX = xpos - lastX;
//    deltaY = ypos - lastY;
//
//    lastX = xpos;
//    lastY = ypos;
//
////    camera.ProcessMouseMovement(deltaX, deltaY);
//}

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


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, const char * argv[]) {
    std::string exePath = argv[0];
    //Open window
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    TwBar *bar;
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //终止
        return -1;
    }
    glfwMakeContextCurrent(window); //绑定使用
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
//    glfwSetCursorPosCallback(window, mouse_callback);
    
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
//    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    TwInit(TW_OPENGL_CORE, NULL);
    TwDefine(" GLOBAL fontSize=24 ");
    TwWindowSize(1600, 1150);
    // Create a tweak bar
    TwBar *mainBar = TwNewBar("Main");
    TwDefine(" Main label='Main TweakBar' refresh=0.5 position='16 16' size='400 400' alpha=0");
    TwAddVarRW(mainBar, "ScaleX", TW_TYPE_FLOAT, &ScaleX, "label='ScaleX' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "ScaleY", TW_TYPE_FLOAT, &ScaleY, "label='ScaleY' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "SplitX", TW_TYPE_FLOAT, &SplitX, "label='SplitX' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "SplitY", TW_TYPE_FLOAT, &SplitY, "label='SplitY' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "TranslationX", TW_TYPE_FLOAT, &TranslationX, "label='TranslationX' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "TranslationY", TW_TYPE_FLOAT, &TranslationY, "label='TranslationY' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "SquareN", TW_TYPE_FLOAT, &SquareN, "label='SquareN' min=-3 max=3 step=0.01 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "SquareScale", TW_TYPE_FLOAT, &SquareScale, "label='SquareScale' min=-3 max=3 step=0.05 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "RotationX", TW_TYPE_FLOAT, &RotationX, "label='RotationX' min=-90 max=90 step=0.1 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "RotationY", TW_TYPE_FLOAT, &RotationY, "label='RotationY' min=-90 max=90 step=0.1 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "RotationZ", TW_TYPE_FLOAT, &RotationZ, "label='RotationZ' min=-90 max=90 step=0.1 keyIncr=u keyDecr=U" );
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
//    glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
    glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW3);
    glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW3);
    glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW3);
    
//    Shader* normalMapShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/vertexSource.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/fragementSource.frag");
    Shader* normalMapShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab5/normalVertex.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab5/normalFrag.frag");
    unsigned int diffuseMap = loadTexture("/Users/buxin/Downloads/egg/egg.jpg");
//    unsigned int normalMap  = loadTexture("/Users/buxin/Downloads/Mandalorian/scracht 2.png");
//    unsigned int diffuseMap = loadTexture("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/brickwall.jpg");
//    unsigned int normalMap  = loadTexture("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/brickwall_normal.jpg");
    Material* myMaterial = new Material(normalMapShader,
                                        LoadImageToGPU("/Users/buxin/Downloads/obj/textures/Apricot_02_diffuse.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
                                        1,
                                        1,
                                        vec3 (1.0f,1.0f,1.0f),
                                        32.0f);
    Model model("/Users/buxin/Downloads/obj/Apricot_02_hi_poly.obj");
    
    mat4 modelMat = mat4(1.0f);
    mat4 viewMat = mat4(1.0f);
    mat4 view = mat4(1.0f);
    mat4 projMat = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //Process input
        processInput(window); //下一帧输入
        //Clear screen
        glClearColor(0.7f,0.8f,0.9f,1.0f); //r,g,b,
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        viewMat = glm::mat4(glm::mat3(camera.GetfirstViewMatrix()));
        view = camera.GetfirstViewMatrix();
        modelMat = translate(mat4(1.0f), vec3(-0.0f,-1,-8.0f));
        modelMat = glm::rotate(modelMat, glm::radians(-15.0f), glm::normalize(glm::vec3(0.0, 1.0, 0.0)));
//        modelMat = glm::rotate(modelMat, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(0.0, 1.0, 0.0)));
//        modelMat = scale(modelMat, vec3(0.05,0.05,0.05));
        normalMapShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"model"),1,GL_FALSE,value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"view"),1,GL_FALSE,value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"projection"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(normalMapShader->ID,"viewPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        
        glUniform3f(glGetUniformLocation(normalMapShader->ID,"halfwayPos"),0.0f,1.5f,-4.0f);
        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightPos"),0.0f,1.5f,-4.0f);
        glUniform1i(glGetUniformLocation(normalMapShader->ID,"diffuseMap"),0);
        glUniform1i(glGetUniformLocation(normalMapShader->ID,"normalMap"),1);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"ScaleX"),ScaleX);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"ScaleY"),ScaleY);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"SplitX"),SplitX);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"SplitY"),SplitY);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"TranslationX"),TranslationX);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"TranslationY"),TranslationY);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"SquareN"),SquareN);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"SquareScale"),SquareScale);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"RotationX"),RotationX);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"RotationY"),RotationY);
        glUniform1f(glGetUniformLocation(normalMapShader->ID,"RotationZ"),RotationZ);
        model.Draw(myMaterial->shader);

        TwDraw();
        //Clean up,prepare for next render loop
        glfwSwapBuffers(window); //切换前后buffer
        glfwPollEvents();
        camera.UpdateCameraPos();
    }
    //Exit Program
    TwTerminate();
    glfwTerminate();
    return 0;
}

