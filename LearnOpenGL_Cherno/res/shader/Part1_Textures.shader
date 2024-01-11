#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

uniform vec2 uResolution;
uniform float uScale;
uniform sampler2D uTexture;

void main()
{
    vec2 st = gl_FragCoord.xy / uResolution;
    st = (st - 0.5) / uScale + 0.5;

    FragColor = texture(uTexture, st);
}