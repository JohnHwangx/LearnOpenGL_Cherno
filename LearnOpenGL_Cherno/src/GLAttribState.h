#pragma once
#include <string>
#include <unordered_map>

typedef std::unordered_map<const char*, char> GLAttribOffsetMap;

class GLAttibState
{
public:
	// 顶点属性：位置坐标
	constexpr static const char		POSITION_BIT = 1 << 0;
	constexpr static const int		POSITION_COMPONENT = 3;
	constexpr static const char*	POSITION_NAME = "aPosition";
	constexpr static const char		POSITION_LOCATION = 0;
	// 顶点属性：纹理坐标0
	constexpr static const char		TEXCOORD_BIT = 1 << 1;
	constexpr static const int		TEXCOORD_COMPONENT = 2;
	constexpr static const char*	TEXCOORD_NAME = "aTexCoord";
	constexpr static const char		TEXCOORD_LOCATION = 1;
	// 顶点属性：纹理坐标1
	constexpr static const char		TEXCOORD1_BIT = 1 << 2;
	constexpr static const int		TEXCOORD1_COMPONENT = 2;
	constexpr static const char*	TEXCOORD1_NAME = "aTexCoord1";
	constexpr static const char		TEXCOORD1_LOCATION = 2;
	// 顶点属性：法向量
	constexpr static const char		NORMAL_BIT = 1 << 3;
	constexpr static const int		NORMAL_COMPONENT = 3;
	constexpr static const char*	NORMAL_NAME = "aNormal";
	constexpr static const char		NORMAL_LOCATION = 3;
	// 顶点属性：切向量
	constexpr static const char		TANGENT_BIT = 1 << 4;
	constexpr static const int		TANGENT_COMPONENT = 4;
	constexpr static const char*	TANGENT_NAME = "aTangent";
	constexpr static const char		TANGENT_LOCATION = 4;
	// 顶点属性：颜色
	constexpr static const char		COLOR_BIT = 1 << 5;
	constexpr static const int		COLOR_COMPONENT = 4;
	constexpr static const char*	COLOR_NAME = "aColor";
	constexpr static const char		COLOR_LOCATION = 5;

	// float类型和uint16类型的字节长度
	constexpr static const int		FLOAT32_SIZE = sizeof(float);
	constexpr static const int		UINT16_SIZE = sizeof(uint16_t);

	constexpr static const char*	ATTRIBSTRIDE = "STRIDE";
	constexpr static const char*	ATTRIBBYTELENGTH = "BYTELENGTH";

	static char MakeVertexAttribs(bool useTexcoord0,
		bool useTexcoord1,
		bool useNormal,
		bool useTangent,
		bool useColor);

	static bool hasPosition(char attribBits);
	static bool hasNormal(char attribBits);
	static bool hasTexCoord_0(char attribBits);
	static bool hasTexCoord_1(char attribBits);
	static bool hasColor(char attribBits);
	static bool hasTangent(char attribBits);

	static char GetVertexByteStride(char attribBits);
	static GLAttribOffsetMap GetInterleavedLayoutAttribOffsetMap(char attribBits);
};