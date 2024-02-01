#include "AttribState.h"

char GLAttibState::MakeVertexAttribs(bool useTexcoord0, bool useTexcoord1, bool useNormal, bool useTangent, bool useColor)
{
	char bits = GLAttibState::POSITION_BIT;

    if (useTexcoord0 == true) {
        bits |= GLAttibState::TEXCOORD_BIT;
    }
    if (useTexcoord1 == true) {
        bits |= GLAttibState::TEXCOORD1_BIT;
    }
    if (useNormal == true) {
        bits |= GLAttibState::NORMAL_BIT;
    }
    if (useTangent == true) {
        bits |= GLAttibState::TANGENT_BIT;
    }
    if (useColor == true) {
        bits |= GLAttibState::COLOR_BIT;
    }

	return bits;
}

bool GLAttibState::hasPosition(char attribBits)
{
    return (attribBits & GLAttibState::POSITION_BIT) != 0;
}

bool GLAttibState::hasNormal(char attribBits)
{
    return false;
}

bool GLAttibState::hasTexCoord_0(char attribBits)
{
    return false;
}

bool GLAttibState::hasTexCoord_1(char attribBits)
{
    return false;
}

bool GLAttibState::hasColor(char attribBits)
{
    return false;
}

bool GLAttibState::hasTangent(char attribBits)
{
    return false;
}

char GLAttibState::GetVertexByteStride(char attribBits)
{
    char byteOffset = 0;
    if (GLAttibState::hasPosition(attribBits))
        byteOffset += GLAttibState::POSITION_COMPONENT * GLAttibState::FLOAT32_SIZE;

    if (GLAttibState::hasNormal(attribBits))
        byteOffset += GLAttibState::NORMAL_COMPONENT * GLAttibState::FLOAT32_SIZE;

    if (GLAttibState::hasTexCoord_0(attribBits))
        byteOffset += GLAttibState::TEXCOORD_COMPONENT * GLAttibState::FLOAT32_SIZE;

    if (GLAttibState::hasTexCoord_1(attribBits))
        byteOffset += GLAttibState::TEXCOORD1_COMPONENT * GLAttibState::FLOAT32_SIZE;

    if (GLAttibState::hasColor(attribBits))
        byteOffset += GLAttibState::COLOR_COMPONENT * GLAttibState::FLOAT32_SIZE;

    if (GLAttibState::hasTangent(attribBits))
        byteOffset += GLAttibState::TANGENT_COMPONENT * GLAttibState::FLOAT32_SIZE;

    return byteOffset;
}

GLAttribOffsetMap GLAttibState::GetInterleavedLayoutAttribOffsetMap(char attribBits)
{
    GLAttribOffsetMap offsets;
    char byteOffset = 0;

    if (GLAttibState::hasPosition(attribBits))
    {
        offsets[GLAttibState::POSITION_NAME] = 0;
        byteOffset += GLAttibState::POSITION_COMPONENT * GLAttibState::FLOAT32_SIZE;
    }

    if (GLAttibState::hasNormal(attribBits))
    {
        offsets[GLAttibState::NORMAL_NAME] = byteOffset;
        byteOffset += GLAttibState::NORMAL_COMPONENT * GLAttibState::FLOAT32_SIZE;
    }
    if (GLAttibState::hasTexCoord_0(attribBits))
    {
        offsets[GLAttibState::TEXCOORD_NAME] = byteOffset;
        byteOffset += GLAttibState::TEXCOORD1_COMPONENT * GLAttibState::FLOAT32_SIZE;
    }
    if (GLAttibState::hasTexCoord_1(attribBits))
    {
        offsets[GLAttibState::TEXCOORD1_NAME] = byteOffset;
        byteOffset += GLAttibState::TEXCOORD1_COMPONENT * GLAttibState::FLOAT32_SIZE;
    }
    if (GLAttibState::hasColor(attribBits))
    {
        offsets[GLAttibState::COLOR_NAME] = byteOffset;
        byteOffset += GLAttibState::COLOR_COMPONENT * GLAttibState::FLOAT32_SIZE;
    }
    if (GLAttibState::hasTangent(attribBits))
    {
        offsets[GLAttibState::TANGENT_NAME] = byteOffset;
        byteOffset += GLAttibState::TANGENT_COMPONENT * GLAttibState::FLOAT32_SIZE;
    }

    offsets[GLAttibState::ATTRIBSTRIDE] = byteOffset;
    offsets[GLAttibState::ATTRIBBYTELENGTH] += byteOffset;

    return offsets;
}
