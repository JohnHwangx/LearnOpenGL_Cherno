#shader vertex
#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 5) in vec4 aColor;

out vec3 vNormals;
out vec2 vTexCoords;
out vec4 vColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    vColor = aColor;
    vTexCoords = aTexCoord;
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 vTexCoords;
in vec4 vColor;
uniform sampler2D uTexture;

void main()
{
    FragColor = mix(vColor, texture(uTexture, vTexCoords), 0.5);
}