#version 330 core
//in vec4 vertexColor;
in vec2 TexCoord;

//in VS_OUT {
//    vec3 FragPos;
//    vec2 TexCoord;
//    vec3 TangentLightPos;
//    vec3 TangentViewPos;
//    vec3 TangentFragPos;
//    mat3 TBN;
//} fs_in;
//struct DirectionalLight
//{
//    vec3 lightDirection;
//    vec3 ambientLight;
//    vec3 diffuseLight;
//    vec3 specularLight;
//    float specularIntensity;
//};
//struct LightPoint{
//    float constant;
//    float linear;//一次项系数
//    float quadratic;//二次项
//    vec3 pos;
//    vec3 color;
//    vec3 dirToLight;
//};
//struct PointLight
//{
//    vec3 lightPosition;
//    vec3 ambientLight;
//    vec3 diffuseLight;
//    vec3 specularLight;
//    float specularIntensity;
//};
//struct Material{
//    vec3 ambient;
//    sampler2D diffuse;
//    sampler2D specular;
//    sampler2D normal;
//    float shininess;
//};
//
//uniform Material material;
//uniform sampler2D diffuseMap;
//uniform sampler2D normalMap;
//uniform DirectionalLight lightD;
//uniform LightPoint lightP;
////uniform PointLight lightP;
//uniform vec3 lightPos;
//uniform vec3 cameraPos;
//uniform float specNum;
//
//out vec4 FragColor;
//vec4 blinnPhongShading(vec3 normal, vec4 color)
//{
//    float sphericalLightRadius = 10.0f;
//    float influenceDistance = 5.0f;
//
//    // Calculate ambient component ---------------------------------------------------------------
//    vec3 ambientComponent = lightD.ambientLight;
//
//    // Calculate diffuse component ---------------------------------------------------------------
//    vec3 diffuseComponent;
//    vec3 lightDir = normalize(-lightD.lightDirection);
//
//    float diffuse = max(dot(normal, lightDir), 0.0f);
//    diffuseComponent = diffuse * lightD.diffuseLight;
//
//    // Calculate specular component --------------------------------------------------------------
//    vec3 viewDirection = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
//    vec3 halfWayDirection = normalize(lightDir + viewDirection);
//    float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.shininess);
//    vec3 specularComponent = specular * lightD.specularLight * lightD.specularIntensity;
//
//    return vec4(ambientComponent + diffuseComponent, 1.0f) * color + vec4(specularComponent, 1.0f);
//}
//vec3 CalcLightPoint(LightPoint light,vec3 uNormal, vec3 dirToCamera){
//    //attenuation
//    float dist = length(light.pos - fs_in.TangentFragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
//    //diffuse max(dot(L,N),0)
//    vec3 lightDir = normalize(light.pos - fs_in.TangentFragPos); //vector pointing to the light,from //fragment pos
//    float diffIntensity = max(dot(lightDir,uNormal),0)* attenuation;
//    vec3 diffColor = texture(material.diffuse, fs_in.TexCoord).rgb * diffIntensity * light.color;
//    //specular pow(max(dot(R,Cam),0),shininess)
//    vec3 viewDirection = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
//    vec3 halfWayDirection = normalize(lightDir + viewDirection);
//    float specular = pow(max(dot(uNormal, halfWayDirection), 0.0f), material.shininess);
////    vec3 specularComponent = specular * light.specularLight * specularIntensity;
//    vec3 R = normalize(reflect(-lightDir,uNormal));//光源指向片源
//    float specIntensity = pow(max(dot(R,dirToCamera),0),material.shininess) * attenuation;
//    vec3 specColor = texture(material.specular,fs_in.TexCoord).rgb*specular * specIntensity * light.color;//uv坐标TexCoord
//
//    vec3 ambient = texture(material.diffuse, fs_in.TexCoord).rgb * 0.2;
//
//    vec3 result = ambient + diffColor+ specColor;
//    return result;
//}
////vec4 blinnPhongShadingPoint(vec3 normal, vec4 color)
////{
////    vec3 totalAmbient = vec3(0.0f, 0.0f, 0.0f);
////    vec3 totalDiffuse = vec3(0.0f, 0.0f, 0.0f);
////    vec3 totalSpecular = vec3(0.0f, 0.0f, 0.0f);
////
////    float kc = 1.0f;
////    float kl = 0.027f;
////    float kq = 0.0028f;
////
////
////        // Calculate ambient component ---------------------------------------------------------------
////        vec3 ambientComponent = lightP.ambientLight * material.ambient;
////
////        // Calculate diffuse component ---------------------------------------------------------------
////        vec3 diffuseComponent, lightVector;
////        lightVector = (lightP.lightPosition - fs_in.TangentFragPos);
////
////
////        float distance = length(lightVector);
////        vec3 lightDir = normalize(lightVector);
////        float diffuse = max(dot(normal, lightDir), 0.0f);
////        diffuseComponent = diffuse * lightP.diffuseLight ;
////
////        // Calculate specular component --------------------------------------------------------------
////        vec3 viewDirection = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
////        vec3 halfWayDirection = normalize(lightDir + viewDirection);
////        float specular = pow(max(dot(normal, halfWayDirection), 0.0f), material.shininess);
////        vec3 specularComponent = specular * lightP.specularLight * lightP.specularIntensity;
////
////        // Calculate the attenuation
////        float attenuation = 1.0f / (kc + kl * distance + kq * (distance * distance));
////
////        totalAmbient += ambientComponent * attenuation;
////        totalDiffuse += diffuseComponent * attenuation;
////        totalSpecular += specularComponent * attenuation;
////
////
////    return vec4(totalAmbient + totalDiffuse, 1.0f) * color + vec4(totalSpecular, 1.0f);
////}
//
//void main(){
//
//    // diffuse
//    vec3 norm = texture(normalMap, fs_in.TexCoord).rgb;
//    norm = normalize(fs_in.TBN*(norm * 2.0 - 1.0));
////    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
//    vec4 diffuseColor = texture(diffuseMap, fs_in.TexCoord);
////    float diff = max(dot(lightDir,norm), 0.0);
////    vec3 diffuse = diff * color;
////    vec3 ambient = 0.6 * color;
//
//    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
//    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
//    FragColor += blinnPhongShading(norm, diffuseColor);
////    FragColor += blinnPhongShadingPoint(norm, diffuseColor);
//    FragColor += vec4(CalcLightPoint(lightP,norm,viewDir),1.0);
////    vec3 reflectDir = reflect(-lightDir, norm);
////    vec3 halfwayDir = normalize(reflectDir + viewDir);
////    float spec = pow(max(dot(norm, halfwayDir), 0.0), specNum);
////    vec3 specular = vec3(0.2) * spec;
////
////    vec3 result = ambient + diffuse + specular;
////    FragColor = vec4(result, 1.0);
////    FragColor = vec4(diffuse,1.0);
//}
//
uniform sampler2D texture_diffuse1;
out vec4 FragColor;
void main()
{
    FragColor = texture(texture_diffuse1, TexCoord);
}
