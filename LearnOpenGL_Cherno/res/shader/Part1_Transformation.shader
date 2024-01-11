#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 v_Color;
out vec2 v_TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    v_Color = aColor;
    v_TexCoord = aTexCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec3 v_Color;
in vec2 v_TexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;
uniform float mixValue;

void main()
{
    FragColor = mix(texture(uTexture1, v_TexCoord), texture(uTexture2, v_TexCoord), mixValue);
}