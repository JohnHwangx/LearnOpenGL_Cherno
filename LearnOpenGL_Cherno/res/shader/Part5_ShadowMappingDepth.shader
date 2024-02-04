#shader vertex
#version 330 core

layout(location = 0) in vec3 aPosition;

uniform mat4 lightSpaceMatrix;
uniform mat4 uModel;

void main()
{
    gl_Position = lightSpaceMatrix * uModel * vec4(aPosition, 1.0);
}

#shader fragment
#version 330 core

void main()
{
    // gl_FragDepth = gl_FragCoord.z;
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}