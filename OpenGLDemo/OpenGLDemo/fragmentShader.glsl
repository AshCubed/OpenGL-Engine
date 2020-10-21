#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffues;
    vec3 specular;
    sampler2D diffuseTex;
    sampler2D specularTex;
};

struct DirLight {
    vec3 direction;
    vec3 color;
    float intensity;

    vec3 ambient;
    vec3 diffues;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    float intensity;
    vec3 color;
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffues;
    vec3 specular;
};

struct SpotLight{
    vec3  position;
    vec3  direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms
uniform Material material;
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLight[NR_POINT_LIGHTS];
#define NR_SPOTPOINT_LIGHTS 4 
uniform SpotLight spotLights[NR_SPOTPOINT_LIGHTS];
uniform DirLight dirLight;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

uniform sampler2D gShadowMap;

//Functions
vec3 calculateAmbient(Material material){
    return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0){
    vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
    float diffuseConst = clamp(dot(posToLightDirVec, normalize(vs_normal)), 0, 1);
    vec3 diffuseFinal = material.diffues * diffuseConst;
    return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos){
    vec3 lightToPosDirVec = normalize(vs_position- lightPos0);
    vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
    vec3 posToViewDirVec = normalize(cameraPos - vs_position);
    float specularConst = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 35);
    //vec3 specularFinal = material.specular * specularConst * texture(material.specularTex, vs_texcoord).rgb;
    vec3 specularFinal = material.specular * specularConst;
    
    return specularFinal;
}

vec3 calculateDirectional(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos){
    vec3 lightToPosDirVec = normalize(-lightPos0);
    float diff = max(dot(vs_normal, lightPos0), 0.0);
    vec3 reflectDirVec = (reflect(lightToPosDirVec, normalize(vs_normal)));
    float specularConst = pow(max(dot(vs_position, reflectDirVec), 0), 35);

    vec3 ambient  = dirLight.ambient  * texture(material.diffuseTex, vs_texcoord).rgb;
    vec3 diffuse  = dirLight.diffues  * diff * texture(material.diffuseTex, vs_texcoord).rgb;
    vec3 specular = dirLight.specular * specularConst * texture(material.specularTex, vs_texcoord).rgb;
    

    return (vec4(ambient, 1.f)) + vec4(diffuse, 1.f) + vec4(specular, 1.f);
}

void main()
{
    vec4 temp;
    
    //Directional Light
    temp += calculateDirectional(material, vs_position, vs_normal, dirLight.direction, cameraPos);

    //All Point Lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        //fs_color = vec4(vs_color, 1.0);
        //fs_color = texture(texture0, vs_texcoord) * vec4(vs_color, 1.0) + texture(texture1, vs_texcoord);

        //Ambient Light
        vec3 ambientFinal = calculateAmbient(material);

        //Diffuse Light
        vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, pointLight[i].position);

        //Specular Light
        vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, pointLight[i].position, cameraPos);

        //Attenuation
        float distance = length(pointLight[i].position - vs_position);
        //constant linear quadratic
        float attenuation = pointLight[i].constant / (1.f + pointLight[i].linear * distance + pointLight[i].quadratic * (distance * distance));


        //Final light
        ambientFinal *= attenuation;
        diffuseFinal *= attenuation;
        specularFinal *= attenuation;

        temp += (vec4(ambientFinal, 1.f)) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f);
    }


    //All Spot Lights
    for(int i = 0; i < NR_SPOTPOINT_LIGHTS; i++){
        vec4 finalSpot;

        float theta = 1.0f + dot(cameraPos, normalize(-spotLights[i].direction)); 
        float epsilon = (spotLights[i].cutOff - spotLights[i].outerCutOff);
        float intensity = clamp((theta - spotLights[i].outerCutOff) / epsilon, 0.0, 500.f);

        vec3 ambientFinal = material.ambient;

        vec3 posToLightDir = normalize(spotLights[i].position - vs_position);
        float diffuse = clamp(dot(posToLightDir, vs_normal), 0, 1);
        vec3 diffuseFinal = material.diffues * diffuse;

        vec3 lightToPosDir = normalize(vs_position - spotLights[i].position);
        vec3 reflectDirVec = normalize(reflect(lightToPosDir, normalize(vs_normal)));
        vec3 posToViewDirVec = normalize(vs_position - cameraPos);
        float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
        vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;


        diffuseFinal  *= intensity;
        specularFinal *= intensity;

        finalSpot = (vec4(specularFinal, 1.f) * vec4(diffuseFinal, 1.f) * vec4(ambientFinal, 1.f));

        temp += finalSpot;
    }

        float Depth = texture(gShadowMap, vs_texcoord).x;
        Depth = 1.0 - (1.0 - Depth) * 25.0;
        

        fs_color = texture(material.diffuseTex, vs_texcoord) * 
        (temp);
        
        //fs_color =  
        //(temp);

}