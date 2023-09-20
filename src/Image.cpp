#define STB_IMAGE_IMPLEMENTATION
#include "Image.hpp"

Image::Image(const std::string& path) : m_width(0), m_height(0), m_channels(0), m_data(nullptr)
{
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
}

Image::Image(Image&& other) noexcept
: m_width(other.m_width),
  m_height(other.m_height),
  m_channels(other.m_channels),
  m_data(other.m_data)
{
    other.m_width = 0;
    other.m_height = 0;
    other.m_channels = 0;
    other.m_data = nullptr;
}

Image& Image::operator=(Image&& other) noexcept
{
    if (this != &other) {
        if (m_data) {
            stbi_image_free(m_data);
        }

        m_width = other.m_width;
        m_height = other.m_height;
        m_channels = other.m_channels;
        m_data = other.m_data;

        other.m_width = 0;
        other.m_height = 0;
        other.m_channels = 0;
        other.m_data = nullptr;
    }

    return *this;
}

Image::~Image()
{
    stbi_image_free(m_data);
}

int Image::GetWidth() const
{
    return m_width;
}

int Image::GetHeight() const
{
    return m_height;
}

int Image::GetChannels() const
{
    return m_channels;
}

unsigned char* Image::GetData() const
{
    return m_data;
}
