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
uniform float PI = 3.1415926536f;
uniform float roughness;

out vec4 FragColor;

void main(){
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float NdotL = max(dot(norm, lightDir), 0.0);
    vec3 cameraVec = normalize(cameraPos - FragPos);
    float NdotV = max(dot(norm, cameraVec), 0.0);
    
    float angleVN = acos(NdotV);
    float angleLN = acos(NdotL);
    
    float roughnessSquared = roughness * roughness;
    float C1 = 1.0 - 0.5 * (roughnessSquared / (roughnessSquared + 0.33));
    float C2 = 0.45 * (roughnessSquared / (roughnessSquared + 0.09));
    
    float alpha = max(angleVN, angleLN);
    float beta = min(angleVN, angleLN);
    float gamma = dot(cameraVec - norm * dot(cameraVec, norm), lightDir - norm * dot(lightDir, norm));
    
    float diffuse = 1;
    float L1 = diffuse * NdotL * (C1 + C2 * max(0,gamma) * sin(alpha) * tan(beta));
    
//    if(gamma >= 0.0) {
//        C2 *= sin(alpha);
//    } else {
//        C2 *= (sin(alpha) - pow((2.0 * beta) / PI, 3.0));
//    }
//    float powValue = (4.0 * alpha * beta) / (PI * PI);
//    float C3  = 0.125 * (roughnessSquared / (roughnessSquared + 0.09)) * powValue * powValue;
//    // now calculate both main parts of the formula
//    float A = gamma * C2 * tan(beta);
//    float B = (1.0 - abs(gamma)) * C3 * tan((alpha + beta) / 2.0);
//    // put it all together
//    float L1 = max(0.0, NdotL) * (C1 + A + B);
        
    vec3 result = L1 * objColor;
    FragColor = vec4(result, 1.0);
//    FragColor = vec4(diffuse,1.0);
}


