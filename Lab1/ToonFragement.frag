#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;//u v坐标

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;
uniform sampler2D ourTexture;
uniform sampler2D ourFace;

uniform vec3 objColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main(){
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir,norm), 0.0);
    vec3 color;
    if (diff<0.2) {
        color = vec3(0.3,0.3,0.3);
    } else if(diff>=0.2 && diff < 0.5){
        color = vec3(0.8,0.8,0.8);
    }else if(diff>=0.5 && diff < 0.85){
        color = vec3(1.0,1.0,1.0);
    }else {
        color = vec3(1.0,2.0,2.0);
    }
    
    vec3 result = color * objColor;
    FragColor = vec4(result, 1.0);
//    FragColor = vec4(diffuse,1.0);
}

