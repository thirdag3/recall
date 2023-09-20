#include "Texture.hpp"

Texture::Texture(const Image& image)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    int channels = image.GetChannels();
    GLenum format;
    switch (channels) {
    case 1:
        format = GL_RED;
        break;

    case 2:
        format = GL_RG;
        break;

    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;

    default:
        format = GL_RGBA;
        break;
    }

    glTextureStorage2D(m_id, 1, GL_RGBA8, image.GetWidth(), image.GetHeight());
    glTextureSubImage2D(m_id, 0, 0, 0, image.GetWidth(), image.GetHeight(), format, GL_UNSIGNED_BYTE, image.GetData());

    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

void Texture::BindToUnit(unsigned int unit)
{
    glBindTextureUnit(unit, m_id);
}
