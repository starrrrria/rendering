#version 330 core
out vec4 FragColor;
#define DegreeToRadian 0.0174533

in VS_OUT {
    vec2 TexCoords;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec3 TangentNormal;
    mat3 TBN;
    vec3 du;
    vec3 dv;
} fs_in;
struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
};
vec3 RotateAroundAxis(vec3 center, vec3 original, vec3 u, float angle)
        {
            original -= center;
            float C = cos(angle);
            float S = sin(angle);
            float t = 1 - C;
            float m00 = t * u.x * u.x + C;
            float m01 = t * u.x * u.y - S * u.z;
            float m02 = t * u.x * u.z + S * u.y;
            float m10 = t * u.x * u.y + S * u.z;
            float m11 = t * u.y * u.y + C;
            float m12 = t * u.y * u.z - S * u.x;
            float m20 = t * u.x * u.z - S * u.y;
            float m21 = t * u.y * u.z + S * u.x;
            float m22 = t * u.z * u.z + C;
            mat3 finalMatrix = mat3(m00, m01, m02, m10, m11, m12, m20, m21, m22);
            return finalMatrix * original + center;
}
float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}
//float smoothstep(float a, float b, float x)
//{
//    float t = saturate((x - a)/(b - a));
//    return t*t*(3.0 - (2.0*t));
//}
uniform Material material;
uniform sampler2D diffuseMap;

uniform vec3 halfwayPos;
uniform vec3 lightPos;

uniform float TranslationX;
uniform float TranslationY;
uniform float RotationX;
uniform float RotationY;
uniform float RotationZ;
uniform float ScaleX;
uniform float ScaleY;
uniform float SplitX;
uniform float SplitY;
uniform float SquareN;
uniform float SquareScale;

void main()
{
    
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
     
    // transform normal vector to range [-1,1]
    vec3 normal = normalize(fs_in.TangentNormal * 2.0 - 1.0);  // this normal is in tangent space
   
    // get diffuse color
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    // halfway
//    vec3 TangentHalfwayPos = fs_in.TBN * halfwayPos;
//    vec3 halfwayDir = normalize(TangentHalfwayPos - fs_in.TangentFragPos);
//    
//    vec3 lightDir =  normalize(2* dot(halfwayDir,viewDir)*halfwayDir - viewDir);
    
    vec3 TangentLightPos = fs_in.TBN * lightPos;
    vec3 lightDir = normalize(TangentLightPos - fs_in.TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diff = max(dot(lightDir, normal), 0.0);
    diff = diff * 0.5 + 0.5;
    vec3 colors;

    if (diff<0.1) {
        colors = vec3(0.1);
    }else if(diff >= 0.1 && diff < 0.3){
        colors = vec3(0.3);
    }else{
        colors = vec3(1.0);
    }

    vec3 diffuse = diff * color * colors*0.5;
    vec3 ambient = 0.4 * color;
    
    vec3 du1 = fs_in.du;
    vec3 dv1 = fs_in.dv;
  
////    //scale
    halfwayDir = halfwayDir - ScaleX * halfwayDir.x * vec3(1, 0, 0);
    halfwayDir = normalize(halfwayDir);
    halfwayDir = halfwayDir - ScaleY * halfwayDir.y * vec3(0, 1, 0);
    halfwayDir = normalize(halfwayDir);
    
    // Ratation
    float xRad = RotationX * DegreeToRadian;
    mat3 xRotation = mat3(1, 0, 0,
                              0, cos(xRad), sin(xRad),
                              0, -sin(xRad), cos(xRad));
    float yRad = RotationY * DegreeToRadian;
    mat3 yRotation = mat3(cos(yRad), 0, -sin(yRad),
                          0, 1, 0,
                          sin(yRad), 0, cos(yRad));
    float zRad = RotationZ * DegreeToRadian;
    mat3 zRotation = mat3(cos(zRad), sin(zRad), 0,
                          -sin(zRad), cos(zRad), 0,
                          0, 0, 1);
    halfwayDir = zRotation * yRotation * xRotation * halfwayDir;
//
//    // Translation
    halfwayDir = halfwayDir + vec3(TranslationX, TranslationY, 0);
    halfwayDir = normalize(halfwayDir);
    
    // Split
    float signX = 1;
    if (halfwayDir.x < 0) {
        signX = -1;
    }
    float signY = 1;
    if (halfwayDir.y < -0.3) {
        signY = -1;
    }
    halfwayDir = halfwayDir - SplitX * signX * vec3(1, 0, 0) - SplitY * signY *vec3(0, 1, 0);
    halfwayDir = normalize(halfwayDir);
    
//    // Square
    float sqrThetaX = acos(halfwayDir.x);
    float sqrThetaY = acos(halfwayDir.y);
    float sqrnormX = sin(pow(2 * sqrThetaX, SquareN));
    float sqrnormY = sin(pow(2 * sqrThetaY, SquareN));
    halfwayDir = halfwayDir - SquareScale * (sqrnormX * halfwayDir.x *vec3(1, 0,0) + sqrnormY * halfwayDir.y * vec3(0, 1, 0));
    halfwayDir = normalize(halfwayDir);
//    
    // specular
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 1.0);
    vec3 highlight;
    if (spec > 0.9) {
        highlight = vec3(1.0);
    }
//    else{
//        highlight = lerp(0, 1, spec);
//    }
    
    vec3 specular = highlight * spec;
    FragColor = vec4(ambient + diffuse + highlight, 1.0);
}
