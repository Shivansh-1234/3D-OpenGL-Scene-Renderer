#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNor;

out vec4 vCol;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vCol = vec4(clamp(aPos, 0.0, 1.0), 1.0);
    TexCoords = aTex;
    Normal = mat3(transpose(inverse(model))) * aNor;
    FragPos = vec3(model * vec4(aPos, 1.0));
}
