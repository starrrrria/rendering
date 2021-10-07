
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

std::vector<std::string> faces
    {
        "/Users/buxin/Documents/real-time-rendering/rendering/skybox/right.jpg",
        "/Users/buxin/Documents/real-time-rendering/rendering/skybox/left.jpg",
        "/Users/buxin/Documents/real-time-rendering/rendering/skybox/top.jpg",
        "/Users/buxin/Documents/real-time-rendering/rendering/skybox/bottom.jpg",
        "/Users/buxin/Documents/real-time-rendering/rendering/skybox/front.jpg",
        "/Users/buxin/Documents/real-time-rendering/rendering/skybox/back.jpg"
    };

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
float* CalTriangle(){
    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


    float quadVertices[] = {
        // positions            // normal         // texcoords  // tangent                          // bitangent
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };
    return quadVertices;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
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

void renderQuad()
{
//    if (quadVAO == 0)
//    {
        // positions
        
        // configure plane VAO
        
//    }
    
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
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
//    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    Shader* skyShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/skyBoxVertex.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/skyBoxFragment.frag");
//    Shader* normalMapShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/vertexSource.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/fragementSource.frag");
    Shader* normalMapShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/normalVertex.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/normalFrag.frag");
    unsigned int cubemapTexture = loadCubemap(faces);
//    unsigned int diffuseMap = loadTexture("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/diffuse.jpg");
//    unsigned int normalMap  = loadTexture("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/normal.png");
    unsigned int diffuseMap = loadTexture("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/brickwall.jpg");
    unsigned int normalMap  = loadTexture("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/brickwall_normal.jpg");
//    Material* myMaterial = new Material(normalMapShader,
//                                        LoadImageToGPU("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/diffuse.jpg", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
//                                        LoadImageToGPU("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/specular.jpg", GL_RGBA, GL_RGBA, Shader::SPECULAR),
//                                        LoadImageToGPU("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/normal.png", GL_RGBA, GL_RGBA, Shader::NORMAL),
//                                        vec3 (1.0f,1.0f,1.0f),
//                                        32.0f);
    Model model("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/backpack.obj");
    
    mat4 modelMat = mat4(1.0f);
    mat4 viewMat = mat4(1.0f);
    mat4 view = mat4(1.0f);
    mat4 projMat = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


    float quadVertices[] = {
        // positions            // normal         // texcoords  // tangent                          // bitangent
        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

        pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };
    
    unsigned int quadVAO, quadVBO;
//    float *quadVertices = CalTriangle();
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //skybox
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //Process input
        processInput(window); //下一帧输入
        //Clear screen
        glClearColor(0.8f,0.8f,0.8f,1.0f); //r,g,b,
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        viewMat = glm::mat4(glm::mat3(camera.GetfirstViewMatrix()));
        view = camera.GetfirstViewMatrix();
        modelMat = translate(mat4(1.0f), vec3(0.0f,0,-2.0f));
        modelMat = glm::rotate(modelMat, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(0.0, 1.0, 0.0)));
//        modelMat = scale(modelMat, vec3(1,1,0.2));
        normalMapShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"model"),1,GL_FALSE,value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"view"),1,GL_FALSE,value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"projection"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(normalMapShader->ID,"viewPos"),camera.Position.x,camera.Position.y,camera.Position.z);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightD.lightDirection"),0.5f,1.0f, -8.0f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightD.ambientLight"),0.2f,0.2f,0.2f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightD.diffuseLight"),1.0f,1.0f,1.0f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightD.specularLight"),1.0f,1.0f,1.0f);
//        glUniform1f(glGetUniformLocation(normalMapShader->ID,"lightD.specularIntensity"),32);
        
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.pos"),0.5f,1.0f, -8.0f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.color"),5.0f,5.0f,5.0f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.direction"),radians(90.0f),0,0);
//        glUniform1f(glGetUniformLocation(normalMapShader->ID,"lightP.constant"),1.0f);
//        glUniform1f(glGetUniformLocation(normalMapShader->ID,"lightP.linear"),0.3f);
//        glUniform1f(glGetUniformLocation(normalMapShader->ID,"lightP.quadratic"),0.0032f);
        
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.lightDirection"),0.5f,2.0f, -8.0f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.ambientLight"),0.2f,0.2f,0.2f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.diffuseLight"),0.2f,0.2f,0.2f);
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightP.specularLight"),0.2f,0.2f,0.2f);
//        glUniform1f(glGetUniformLocation(normalMapShader->ID,"lightP.specularIntensity"),32);
        
//        myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
//        myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
//        myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
//        myMaterial->shader->SetUniform1i("material.normal", Shader::NORMAL);
//        myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
        
        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightPos"),0.5f,0.0f, -2.0f);
        glUniform1i(glGetUniformLocation(normalMapShader->ID,"diffuseMap"),0);
        glUniform1i(glGetUniformLocation(normalMapShader->ID,"normalMap"),1);
        
        renderQuad();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalMap);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
//        model.Draw(myMaterial->shader);
        
//        glm:: mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.5f,1.0f, 0.5f));
//        model = glm::scale(model, glm::vec3(0.1f));
//        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"modelMat"),1,GL_FALSE,value_ptr(model));
//        glBindVertexArray(quadVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, normalMap);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        glBindVertexArray(0);
//        renderQuad();
        // cubes
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
        
        
        glDepthFunc(GL_LEQUAL);
        skyShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(skyShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(skyShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform1i(glGetUniformLocation(skyShader->ID,"skybox"),0);
        
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        

        //Clean up,prepare for next render loop
        glfwSwapBuffers(window); //切换前后buffer
        glfwPollEvents();
        camera.UpdateCameraPos();
    }
    //Exit Program
    glfwTerminate();
    return 0;
}

