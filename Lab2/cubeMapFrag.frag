#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform vec3 fresnelBase = vec3(0.1);
uniform vec3 fresnelScale = vec3(0.3);
uniform float dispersionFactor=1.5f; //Dispersion enhancement,1 is not enhanced
//uniform float fresnelIndensity = 5;
//uniform vec4 fresnelCol = vec4(1,1,1,1);
uniform vec3 lightPos=vec3(3.0, 0.0, 0.0);

void main()
{
//Combine
    
    vec3 ratio = vec3(0.9967f*dispersionFactor,1.0f,1.012f*dispersionFactor)/ 1.52;
    
    vec3 V=normalize(cameraPos-FragPos);
    vec3 N=normalize(Normal);
    vec3 H=normalize(V+N);
    vec3 kS=fresnelBase+fresnelScale*pow(1.0-dot(H,V),5.0);
    
    vec3 reflectVec= reflect(-V,N)*kS;
    vec3 refractionVec=normalize(-V);
    
    vec3 tRed=refract(refractionVec,N,ratio.x);
    vec3 tGreen=refract(refractionVec,N,ratio.y);
    vec3 tBlue=refract(refractionVec,N,ratio.z);
    
    vec4 reflectedColor = vec4(texture(skybox, reflectVec).rgb,1.0);
    vec3 Color=vec3(tRed.r,tGreen.g,tBlue.b);
    vec4 refractedColor = vec4(texture(skybox, Color).rgb,1.0);
    
    float ratio_r=0.44f;
    float ratio_t=0.73f;
    
    FragColor = refractedColor*ratio_t+reflectedColor*ratio_r;
    
//Refraction
    
//    float ratio = 1.00 / 1.52;
//
//    vec3 V=normalize(cameraPos-FragPos);
//    vec3 N=normalize(-Normal);
//    vec3 H=normalize(V+N);
//    vec3 kS=fresnelBase+fresnelScale*pow(1.0-dot(H,V),5.0);
//
//    vec3 I = normalize(FragPos - cameraPos);
//    vec3 R = refract(I, normalize(Normal), ratio)*kS;
//
//    //the light color r,g,b have different extents to refract
//    float r=R[0]*0.9967;
//    float g=R[1]*1;
//    float b=R[2]*1.012;
//    vec3 color=vec3(r,g,b);
//    FragColor = vec4(texture(skybox, color).rgb,1.0);
    
//Fresnel
    //    vec3 V=normalize(cameraPos-FragPos);
    //    vec3 N=normalize(-Normal);
    //    vec3 H=normalize(V+N);
    //    vec3 kS=fresnelBase+fresnelScale*pow(1.0-dot(H,V),5.0);
    //
    //    vec3 I = normalize(FragPos - cameraPos);
    //    vec3 R = reflect(I, normalize(Normal))*kS;
    //    FragColor = vec4(texture(skybox, R).rgb,1.0);

}
