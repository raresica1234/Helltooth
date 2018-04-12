#ifdef HT_OPENGL
#include "graphics/Texture2D.hpp"

namespace ht { namespace graphics {

	void Texture2D::SetSamplerState() {
		GL(glGenerateMipmap(GL_TEXTURE_2D));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.4f));
	}

	Texture2D::Texture2D(u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		GL(glGenTextures(1, &m_Texture));
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, nullptr));
		SetSamplerState();
	}

	Texture2D::Texture2D(byte* pixels, u32 width, u32 height, TextureFormat format) : Texture(width, height, TextureType::TEXTURE_2D, format) {
		GL(glGenTextures(1, &m_Texture));
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(format), width, height, 0, static_cast<GLenum>(GetBaseFormat(format)), GL_UNSIGNED_BYTE, pixels));
		SetSamplerState();
	}

	Texture2D::~Texture2D() {
		GL(glDeleteTextures(1, &m_Texture));
	}

	void Texture2D::SetPixels(byte* pixels) {
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(m_Format), m_Width, m_Height, 0, static_cast<GLenum>(GetBaseFormat(m_Format)), GL_UNSIGNED_BYTE, pixels));
	}

	void Texture2D::Bind(u32 slot) {
		GL(glBindTexture(GL_TEXTURE_2D, m_Texture));
		GL(glActiveTexture(GL_TEXTURE0 + slot));
	}

} }

#endif // HT_OPENGL