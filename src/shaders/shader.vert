#version 150

in vec4 position;
in vec4 color;

out vec4 Color;

uniform mat4 mvpTransform;

void main()
{
    Color = color;
    gl_Position = mvpTransform * position;
}
