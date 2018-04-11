#pragma once

#if defined(HT_OPENGL)
#include "platform/opengl/GL.hpp"
#elif defined(HT_DIRECTX)
#include <d3d11.h>
#endif // HT_OPENGL

#include "core/Internal.hpp"

#include "utils/Log.hpp"

namespace ht { namespace graphics {

	enum class BufferUsage {
#if defined(HT_OPENGL)
		STATIC  = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
#elif defined(HT_DIRECTX)
		STATIC  = D3D11_USAGE_DEFAULT,
		DYNAMIC = D3D11_USAGE_DYNAMIC
#endif // HT_OPENGL
	};

	enum class DataType {
		VECTOR2,
		VECTOR3,
		VECTOR4,
		MATRIX4,
		TEXTURE_2D,
#if defined(HT_OPENGL)
		FLOAT           = GL_FLOAT,
		UNSIGNED_SHORT  = GL_UNSIGNED_SHORT,
		UNSIGNED_INT    = GL_UNSIGNED_INT,
		UNSIGNED_BYTE   = GL_UNSIGNED_BYTE,
#elif defined(HT_DIRECTX)
		FLOAT           = DXGI_FORMAT_R32_FLOAT,
		UNSIGNED_SHORT  = DXGI_FORMAT_R16_UINT,
		UNSIGNED_INT    = DXGI_FORMAT_R32_UINT,
		UNSIGNED_BYTE   = DXGI_FORMAT_R8_UINT,
#endif // HT_OPENGL
		
	};

	enum class ShaderType {
#if defined(HT_OPENGL)
		VERTEX    = GL_VERTEX_SHADER,
		FRAGMENT  = GL_FRAGMENT_SHADER,
#elif defined(HT_DIRECTX)
		VERTEX,
		FRAGMENT,
#endif // HT_OPENGL
		UNKOWN,
	};

	enum class TextureFormat {
		UNKNOWN = 0,
#if defined(HT_OPENGL)
		RGB   = GL_RGB,
		RGBA  = GL_RGBA,
		BGRA  = GL_BGRA,
#elif defined(HT_DIRECTX)
		RGB   = UNKNOWN, // no support
		RGBA  = DXGI_FORMAT_R8G8B8A8_UNORM,
		BGRA  = DXGI_FORMAT_B8G8R8A8_UNORM,
#endif // HT_OPENGL
	};

	enum class TextureType {
		UNKNOWN,
		TEXTURE_2D,
		TEXTURE_3D
	};

	enum ShaderLocationType {
		FROM_MEMORY = 00,
		FROM_PATH   = 01,
		FROM_HTSL   = 10
	};

	enum class BufferMapType {
#if defined(HT_OPENGL)
		READ_ONLY       = GL_READ_ONLY,
		WRITE_ONLY      = GL_WRITE_ONLY,
		READ_AND_WRITE  = GL_READ_WRITE,
#elif defined(HT_DIRECTX)
		READ_ONLY       = D3D11_MAP_READ,
		WRITE_ONLY      = D3D11_MAP_WRITE,
		READ_AND_WRITE  = D3D11_MAP_READ_WRITE,
#endif // HT_OPENGL
	};

	extern u32 DataTypeSize(DataType type);
	extern u32 TextureFormatSize(TextureFormat type);
	extern u32 GetSemanticIndex(DataType type);
	extern TextureFormat GetFormat(u32 bpp);
	extern TextureFormat GetBaseFormat(TextureFormat);

} }