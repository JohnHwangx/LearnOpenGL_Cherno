#shader vertex
#version 330 core
layout (location = 0) in vec3 aPosition;
//layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoords;

void main()
{
    //TexCoords = aTexCoord;
    gl_Position = vec4(aPosition, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

//in vec2 TexCoords;
//uniform sampler2D uTexture;

void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}