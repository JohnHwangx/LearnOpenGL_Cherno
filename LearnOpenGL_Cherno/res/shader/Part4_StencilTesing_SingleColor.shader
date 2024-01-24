#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos, 1.0);
};

#shader fragment
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.04, 0.28, 0.26, 1.0);
}