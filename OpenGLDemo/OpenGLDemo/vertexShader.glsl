#version 330 core

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec2 vertex_texcoord;
layout (location = 3) in vec3 vertex_normal;
layout (location = 4) in vec3 vertex_Tangent;
layout (location = 5) in vec3 vertex_Bitangent;  

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;
out vec3 vs_normal;
out vec4 FragPosLightSpace;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 lightSpaceMatrix;


uniform mat4 gWVP;


void main()
{
    vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
    vs_color = vertex_color;
    vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
    vs_normal = mat3(ModelMatrix) * vertex_normal;
    FragPosLightSpace = lightSpaceMatrix * vec4(vs_position, 1.0);

    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix   * vec4(vertex_position, 1.f);
}