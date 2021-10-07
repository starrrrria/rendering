#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT {
    vec2 TexCoords;
    vec3 TangentNormal;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    mat3 TBN;
    vec3 du;
    vec3 dv;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 viewPos;
uniform float RotationX;
uniform float RotationY;
uniform float RotationZ;

void main()
{
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;
    
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    vs_out.du = aTangent;
    vs_out.dv = normalize(aNormal * aTangent);
    
    vs_out.TBN = transpose(mat3(T, B, N));
    vs_out.TangentViewPos  = vs_out.TBN * viewPos;
    vs_out.TangentFragPos  = vs_out.TBN * FragPos;
    vs_out.TangentNormal = vs_out.TBN * aNormal;
    
//    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
  
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
