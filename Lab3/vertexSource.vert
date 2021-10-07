#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTexCoord;
//layout (location = 3) in vec3 aTangent;
//layout (location = 4) in vec3 aBitangent;

//out VS_OUT {
//    vec3 FragPos;
//    vec2 TexCoord;
//    vec3 TangentLightPos;
//    vec3 TangentViewPos;
//    vec3 TangentFragPos;
//    mat3 TBN;
//} vs_out;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec4 vertexColor;
out vec2 TexCoord;
//uniform vec3 lightPos;
//uniform vec3 cameraPos;

void main(){
//    vs_out.FragPos = vec3(modelMat * vec4(aPos.xyz, 1.0)); //补1表示顶点
//    vs_out.TexCoord = aTexCoord;
    
//    mat3 normalMatrix = transpose(inverse(mat3(modelMat)));
//    vec3 T = normalize(vec3(modelMat * vec4(aTangent, 0.0)));
//    vec3 N = normalize(vec3(modelMat * vec4(aNormal, 0.0)));
    
//    vec3 T = normalize(normalMatrix * aTangent);
//    vec3 N = normalize(normalMatrix * aNormal);
//    T = normalize(T - dot(T, N) * N);
//    vec3 B = cross(N, T);
    
//    vs_out.TBN = transpose(mat3(T, B, N));
//    vs_out.TangentLightPos = vs_out.TBN * lightPos;
//    vs_out.TangentViewPos  = vs_out.TBN * cameraPos;
//    vs_out.TangentFragPos  = vs_out.TBN * vs_out.FragPos;
    
    gl_Position = projMat * viewMat * modelMat * vec4(aPos,1.0);
    
    //vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0);
    TexCoord = aTexCoord;
}
