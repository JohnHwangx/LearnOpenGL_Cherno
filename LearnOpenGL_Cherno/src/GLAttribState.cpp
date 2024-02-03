#include "GLAttribState.h"
#include "Renderer.h"

char GLAttribState::MakeVertexAttribs(bool useTexcoord0, bool useTexcoord1, bool useNormal, bool useTangent, bool useColor)
{
	char bits = GLAttribState::POSITION_BIT;

    if (useTexcoord0 == true) {
        bits |= GLAttribState::TEXCOORD_BIT;
    }
    if (useTexcoord1 == true) {
        bits |= GLAttribState::TEXCOORD1_BIT;
    }
    if (useNormal == true) {
        bits |= GLAttribState::NORMAL_BIT;
    }
    if (useTangent == true) {
        bits |= GLAttribState::TANGENT_BIT;
    }
    if (useColor == true) {
        bits |= GLAttribState::COLOR_BIT;
    }

	return bits;
}

bool GLAttribState::hasPosition(char attribBits)
{
    return (attribBits & GLAttribState::POSITION_BIT) != 0;
}

bool GLAttribState::hasNormal(char attribBits)
{
    return (attribBits & GLAttribState::NORMAL_BIT) != 0;
}

bool GLAttribState::hasTexCoord_0(char attribBits)
{
    return (attribBits & GLAttribState::TEXCOORD_BIT) != 0;
}

bool GLAttribState::hasTexCoord_1(char attribBits)
{
    return (attribBits & GLAttribState::TEXCOORD1_BIT) != 0;
}

bool GLAttribState::hasColor(char attribBits)
{
    return (attribBits & GLAttribState::COLOR_BIT) != 0;
}

bool GLAttribState::hasTangent(char attribBits)
{
    return (attribBits & GLAttribState::TANGENT_BIT) != 0;
}

char GLAttribState::GetVertexByteStride(char attribBits)
{
    char byteOffset = 0;
    if (GLAttribState::hasPosition(attribBits))
        byteOffset += GLAttribState::POSITION_COMPONENT * GLAttribState::FLOAT32_SIZE;

    if (GLAttribState::hasNormal(attribBits))
        byteOffset += GLAttribState::NORMAL_COMPONENT * GLAttribState::FLOAT32_SIZE;

    if (GLAttribState::hasTexCoord_0(attribBits))
        byteOffset += GLAttribState::TEXCOORD_COMPONENT * GLAttribState::FLOAT32_SIZE;

    if (GLAttribState::hasTexCoord_1(attribBits))
        byteOffset += GLAttribState::TEXCOORD1_COMPONENT * GLAttribState::FLOAT32_SIZE;

    if (GLAttribState::hasColor(attribBits))
        byteOffset += GLAttribState::COLOR_COMPONENT * GLAttribState::FLOAT32_SIZE;

    if (GLAttribState::hasTangent(attribBits))
        byteOffset += GLAttribState::TANGENT_COMPONENT * GLAttribState::FLOAT32_SIZE;

    return byteOffset;
}

GLAttribOffsetMap GLAttribState::GetInterleavedLayoutAttribOffsetMap(char attribBits)
{
    GLAttribOffsetMap offsets;
    unsigned int byteOffset = 0;

    if (GLAttribState::hasPosition(attribBits))
    {
        offsets[GLAttribState::POSITION_NAME] = 0;
        byteOffset += GLAttribState::POSITION_COMPONENT * GLAttribState::FLOAT32_SIZE;
    }

    if (GLAttribState::hasNormal(attribBits))
    {
        offsets[GLAttribState::NORMAL_NAME] = byteOffset;
        byteOffset += GLAttribState::NORMAL_COMPONENT * GLAttribState::FLOAT32_SIZE;
    }
    if (GLAttribState::hasTexCoord_0(attribBits))
    {
        offsets[GLAttribState::TEXCOORD_NAME] = byteOffset;
        byteOffset += GLAttribState::TEXCOORD1_COMPONENT * GLAttribState::FLOAT32_SIZE;
    }
    if (GLAttribState::hasTexCoord_1(attribBits))
    {
        offsets[GLAttribState::TEXCOORD1_NAME] = byteOffset;
        byteOffset += GLAttribState::TEXCOORD1_COMPONENT * GLAttribState::FLOAT32_SIZE;
    }
    if (GLAttribState::hasColor(attribBits))
    {
        offsets[GLAttribState::COLOR_NAME] = byteOffset;
        byteOffset += GLAttribState::COLOR_COMPONENT * GLAttribState::FLOAT32_SIZE;
    }
    if (GLAttribState::hasTangent(attribBits))
    {
        offsets[GLAttribState::TANGENT_NAME] = byteOffset;
        byteOffset += GLAttribState::TANGENT_COMPONENT * GLAttribState::FLOAT32_SIZE;
    }

    offsets[GLAttribState::ATTRIBSTRIDE] = byteOffset;
    offsets[GLAttribState::ATTRIBBYTELENGTH] += byteOffset;

    return offsets;
}

void GLAttribState::SetAttribVertexArrayPointer(GLAttribOffsetMap offsetMap)
{
    unsigned int stride = offsetMap[GLAttribState::ATTRIBSTRIDE];
    if (stride == 0)
        throw;

    if (stride != offsetMap[GLAttribState::ATTRIBBYTELENGTH])
        stride = 0;

    unsigned int offset = offsetMap[GLAttribState::POSITION_NAME];
    if (offsetMap.find(GLAttribState::POSITION_NAME) != offsetMap.end())
    {
        GLCall(glVertexAttribPointer(
            GLAttribState::POSITION_LOCATION,
            GLAttribState::POSITION_COMPONENT,
            GL_FLOAT,
            false,
            stride,
            (void*)offset));
    }
    if (offsetMap.find(GLAttribState::NORMAL_NAME) != offsetMap.end())
    {
        offset = offsetMap[GLAttribState::NORMAL_NAME];
        GLCall(glVertexAttribPointer(
            GLAttribState::NORMAL_LOCATION,
            GLAttribState::NORMAL_COMPONENT,
            GL_FLOAT,
            false,
            stride,
            (void*)offset));
    }
    if (offsetMap.find(GLAttribState::TEXCOORD_NAME) != offsetMap.end())
    {
        offset = offsetMap[GLAttribState::TEXCOORD_NAME];
        GLCall(glVertexAttribPointer(
            GLAttribState::TEXCOORD_LOCATION,
            GLAttribState::TEXCOORD_COMPONENT,
            GL_FLOAT,
            false,
            stride,
            (void*)offset));
    }
    if (offsetMap.find(GLAttribState::TEXCOORD1_NAME) != offsetMap.end())
    {
        offset = offsetMap[GLAttribState::TEXCOORD1_NAME];
        GLCall(glVertexAttribPointer(
            GLAttribState::TEXCOORD1_LOCATION,
            GLAttribState::TEXCOORD1_COMPONENT,
            GL_FLOAT,
            false,
            stride,
            (void*)offset));
    }
    if (offsetMap.find(GLAttribState::COLOR_NAME) != offsetMap.end())
    {
        offset = offsetMap[GLAttribState::COLOR_NAME];
        GLCall(glVertexAttribPointer(
            GLAttribState::COLOR_LOCATION,
            GLAttribState::COLOR_COMPONENT,
            GL_FLOAT,
            false,
            stride,
            (void*)offset));
    }
    if (offsetMap.find(GLAttribState::TANGENT_NAME) != offsetMap.end())
    {
        offset = offsetMap[GLAttribState::TANGENT_NAME];
        GLCall(glVertexAttribPointer(
            GLAttribState::TANGENT_LOCATION,
            GLAttribState::TANGENT_COMPONENT,
            GL_FLOAT,
            false,
            stride,
            (void*)offset));
    }
}

void GLAttribState::SetAttribVertexArrayState(char attribBits, bool enable)
{
    if (GLAttribState::hasPosition(attribBits))
        if (enable)
        {
            GLCall(glEnableVertexAttribArray(GLAttribState::POSITION_LOCATION));
        }
        else
        {
            GLCall(glDisableVertexAttribArray(GLAttribState::POSITION_LOCATION));
        }
    else 
    {
        GLCall(glDisableVertexAttribArray(GLAttribState::POSITION_LOCATION));
    }

    if (GLAttribState::hasNormal(attribBits))
        if (enable) 
        {
            GLCall(glEnableVertexAttribArray(GLAttribState::NORMAL_LOCATION));
        }
        else
        {
            GLCall(glDisableVertexAttribArray(GLAttribState::NORMAL_LOCATION));
        }
    else
    {
        GLCall(glDisableVertexAttribArray(GLAttribState::NORMAL_LOCATION));
    }

    if (GLAttribState::hasTexCoord_0(attribBits))
        if (enable) 
        {
            GLCall(glEnableVertexAttribArray(GLAttribState::TEXCOORD_LOCATION));
        }
        else
        {
            GLCall(glDisableVertexAttribArray(GLAttribState::TEXCOORD_LOCATION));
        }
    else
    {
        GLCall(glDisableVertexAttribArray(GLAttribState::TEXCOORD_LOCATION));
    }

    if (GLAttribState::hasTexCoord_1(attribBits))
        if (enable) 
        {
            GLCall(glEnableVertexAttribArray(GLAttribState::TEXCOORD1_LOCATION));
        }
        else
        {
            GLCall(glDisableVertexAttribArray(GLAttribState::TEXCOORD1_LOCATION));
        }
    else
    {
        GLCall(glDisableVertexAttribArray(GLAttribState::TEXCOORD1_LOCATION));
    }

    if (GLAttribState::hasColor(attribBits))
        if (enable) 
        {
            GLCall(glEnableVertexAttribArray(GLAttribState::COLOR_LOCATION));
        }
        else
        {
            GLCall(glDisableVertexAttribArray(GLAttribState::COLOR_LOCATION));
        }
    else
    {
        GLCall(glDisableVertexAttribArray(GLAttribState::COLOR_LOCATION));
    }

    if (GLAttribState::hasTangent(attribBits))
        if (enable) 
        {
            GLCall(glEnableVertexAttribArray(GLAttribState::TANGENT_LOCATION));
        }
        else
        {
            GLCall(glDisableVertexAttribArray(GLAttribState::TANGENT_LOCATION));
        }
    else
    {
        GLCall(glDisableVertexAttribArray(GLAttribState::TANGENT_LOCATION));
    }
}
