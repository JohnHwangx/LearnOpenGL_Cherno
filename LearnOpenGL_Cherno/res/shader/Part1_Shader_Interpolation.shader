#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1

out vec3 v_Color;

void main()
{
    v_Color = aColor;
    gl_Position = vec4(aPos, 1.0);
};

#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 v_Color; // 在OpenGL程序代码中设定这个变量

void main()
{
    FragColor = vec4(v_Color, 1.0f);
};