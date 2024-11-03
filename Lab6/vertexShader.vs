#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;  // Add color attribute
out vec4 color;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    color = vec4(aColor, 1.0);  // Pass color to fragment shader
}