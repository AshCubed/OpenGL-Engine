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
};

struct PointLight{
    vec3 position;
    float intensity;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    vec3  position;
    vec3  direction;
    float cutOff;
    float outerCutOff;
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

vec3 calculateDIRDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0){
    vec3 posToLightDirVec = normalize(-lightPos0);
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

void main()
{
    vec4 temp;
    
    //Directional Light
    vec3 directionalAmbientFinal = calculateAmbient(material);
    vec3 directionalDiffuseFinal = calculateDIRDiffuse(material, vs_position, vs_normal, dirLight.direction);
    vec3 directionalSpecularFinal = calculateSpecular(material, vs_position, vs_normal, dirLight.direction, cameraPos);
    temp += (vec4(directionalAmbientFinal, 1.f)) + vec4(directionalDiffuseFinal, 1.f) 
        + vec4(directionalSpecularFinal, 1.f);


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
        vec3 lightDir = normalize(spotLights[i].position - vs_position);
        float theta = dot(lightDir, normalize(-spotLights[i].direction));
        float epsilon = (spotLights[i].cutOff - spotLights[i].outerCutOff);
        float intensity = clamp((theta - spotLights[i].outerCutOff) / epsilon, 0.0, 1.0);

        vec3 spotLightDiffuseFinal;
        spotLightDiffuseFinal *= intensity;
        vec3 spotLightSpecularFinal;
        spotLightSpecularFinal *= intensity;

        temp += vec4(spotLightDiffuseFinal, 1.f) + vec4(spotLightSpecularFinal, 1.f);
    }


        fs_color = texture(material.diffuseTex, vs_texcoord) * 
        (temp);

        fs_color =  
        (temp);

    
}