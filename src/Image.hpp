#pragma once

#include <string>

#include <stb/stb_image.h>

class Image
{
  public:
    Image(const std::string& path);
    Image(const Image& other) = delete;
    Image& operator=(const Image& other) = delete;
    Image(Image&& other) noexcept;
    Image& operator=(Image&& other) noexcept;
    ~Image();
    int GetWidth() const;
    int GetHeight() const;
    int GetChannels() const;
    unsigned char* GetData() const;

  private:
    int m_width;
    int m_height;
    int m_channels;
    unsigned char* m_data;
};
