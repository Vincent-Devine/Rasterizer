#include<cstring>

#include <Framebuffer.hpp>

Framebuffer::Framebuffer(int p_width, int p_height)
    : width(p_width)
    , height(p_height)
    , colorBuffer(p_width* p_height)
    , depthBuffer(p_width* p_height)
{
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
}

Framebuffer::~Framebuffer()
{
    glDeleteTextures(1, &colorTexture);
}

void Framebuffer::Clear()
{
    // Sadly too slow...
    //std::fill(colorBuffer.begin(), colorBuffer.end(), clearColor);
    //std::fill(depthBuffer.begin(), depthBuffer.end(), 0.f);

    // Clear color buffer
    {
        Vec4* colors = colorBuffer.data();

        for (std::size_t i = 0; i < (size_t)(width * height); ++i)
            colors[i] = clearColor;

        // // Fill the first line with the clear color
        // for (std::size_t i = 0; i < (size_t)width; ++i)
        //     std::memcpy(&colors[i], &clearColor, sizeof(Vec4));

        // // Copy the first line onto every line
        // for (std::size_t i = 1; i < (size_t)height; ++i)
        //     std::memcpy(&colors[i * width], &colors[0], width * sizeof(Vec4));
    }

    // Clear depth buffer
    {
        for(float& f: depthBuffer)
            f = 15.f;
        // std::memset(depthBuffer.data(), 0, depthBuffer.size() * sizeof(depthBuffer[0]));
    }
}

void Framebuffer::UpdateTexture()
{
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, colorBuffer.data());
}
