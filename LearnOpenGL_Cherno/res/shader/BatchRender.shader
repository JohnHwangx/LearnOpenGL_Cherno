#shader vertex
#version 330 core

layout(location = 0)in vec4 position;
layout(location = 1)in vec4 color;
layout(location = 2)in vec2 texCoord;
layout(location = 3)in float textureIndex;

uniform mat4 u_MVP;

out vec4 v_color;
out vec2 v_texCoord;
out float v_textureIndex;

void main()
{
	v_color = color;
	v_texCoord = texCoord;
	v_textureIndex = textureIndex;
	gl_Position = u_MVP * position;
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

in vec4 v_color;
in vec2 v_texCoord;
in float v_textureIndex;

uniform sampler2D u_Textures[2];

void main()
{
	int idx = int(v_textureIndex);
	vec4 textColor = texture(u_Textures[idx], v_texCoord);
	color = textColor;
};