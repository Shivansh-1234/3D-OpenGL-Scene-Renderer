#version 330 core

in vec4 vCol;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D brickTexture;

void main()
{
    FragColor = texture(brickTexture, TexCoords);
}
