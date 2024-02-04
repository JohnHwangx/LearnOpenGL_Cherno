#pragma once
#include <string>
#include <unordered_map>

namespace Blaze {

	typedef std::unordered_map<const char*, unsigned int> GLAttribOffsetMap;

	class GLAttribState
	{
	public:
		// �������ԣ�λ������
		constexpr static const char			POSITION_BIT = 1 << 0;
		constexpr static const int			POSITION_COMPONENT = 3;
		constexpr static const char* POSITION_NAME = "aPosition";
		constexpr static const unsigned int	POSITION_LOCATION = 0;
		// �������ԣ���������0
		constexpr static const char			TEXCOORD_BIT = 1 << 1;
		constexpr static const int			TEXCOORD_COMPONENT = 2;
		constexpr static const char* TEXCOORD_NAME = "aTexCoord";
		constexpr static const unsigned int	TEXCOORD_LOCATION = 1;
		// �������ԣ���������1
		constexpr static const char			TEXCOORD1_BIT = 1 << 2;
		constexpr static const int			TEXCOORD1_COMPONENT = 2;
		constexpr static const char* TEXCOORD1_NAME = "aTexCoord1";
		constexpr static const unsigned int	TEXCOORD1_LOCATION = 2;
		// �������ԣ�������
		constexpr static const char			NORMAL_BIT = 1 << 3;
		constexpr static const int			NORMAL_COMPONENT = 3;
		constexpr static const char* NORMAL_NAME = "aNormal";
		constexpr static const unsigned int	NORMAL_LOCATION = 3;
		// �������ԣ�������
		constexpr static const char			TANGENT_BIT = 1 << 4;
		constexpr static const int			TANGENT_COMPONENT = 4;
		constexpr static const char* TANGENT_NAME = "aTangent";
		constexpr static const unsigned int	TANGENT_LOCATION = 4;
		// �������ԣ���ɫ
		constexpr static const char			COLOR_BIT = 1 << 5;
		constexpr static const int			COLOR_COMPONENT = 4;
		constexpr static const char* COLOR_NAME = "aColor";
		constexpr static const unsigned int	COLOR_LOCATION = 5;

		// float���ͺ�uint16���͵��ֽڳ���
		constexpr static const unsigned int	FLOAT32_SIZE = sizeof(float);
		constexpr static const unsigned int	UINT16_SIZE = sizeof(uint16_t);

		constexpr static const char* ATTRIBSTRIDE = "STRIDE";
		constexpr static const char* ATTRIBBYTELENGTH = "BYTELENGTH";

		static char MakeVertexAttribs(const bool useTexcoord0,
			const bool useTexcoord1,
			const bool useNormal,
			const bool useTangent,
			const bool useColor);

		static bool hasPosition(const char attribBits);
		static bool hasNormal(const char attribBits);
		static bool hasTexCoord_0(const char attribBits);
		static bool hasTexCoord_1(const char attribBits);
		static bool hasColor(const char attribBits);
		static bool hasTangent(const char attribBits);

		static unsigned int GetVertexBufferSize(const char attribBits, const unsigned int vertexCount);
		static char GetVertexByteStride(const char attribBits);
		static GLAttribOffsetMap GetInterleavedLayoutAttribOffsetMap(const char attribBits);
		static void SetAttribVertexArrayPointer(GLAttribOffsetMap& offsetMap);
		static void SetAttribVertexArrayState(const char attribBits, const  bool enable = true);
	};
}