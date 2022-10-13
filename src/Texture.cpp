#include <Texture.hpp>
#include <stb_image.h>
#include <cmath>
#include <iostream>

void Texture::LoadTexture(const char* fileName)
{
    int channels;
    float* u_pixels = stbi_loadf(fileName, &width, &height, &channels, STBI_rgb_alpha);
    int size = width * height;
    
    pixels.resize(size);
    for (int i = 0; i < size; i++)
    {
        pixels[i].x = u_pixels[i*4];
        pixels[i].y = u_pixels[i*4+1];
        pixels[i].z = u_pixels[i*4+2];
        pixels[i].w = u_pixels[i*4+3];
    }

    free(u_pixels);
}

Vec4 Texture::GetSample(Vec2 uv)
{
    float s = uv.y * height;
    float t = uv.x * width;
    int result = (int)s * width + (int)t;
    if(result > (int)(height * width))
        return (Vec4){1.f, 0.f, 0.5f, 1.f};
    return pixels.at(result);
}

Vec4 Texture::GetBilinearFilteredPixelColor(Vec2 uv) 
{
   float x = floorf(uv.x);
   float y = floorf(uv.y);
   float u_ratio = uv.x - x;
   float v_ratio = uv.y - y;
   float u_opposite = 1 - u_ratio;
   float v_opposite = 1 - v_ratio;
   Vec4 result = (GetSample((Vec2){uv.x,uv.y}) * u_opposite           + GetSample((Vec2){uv.x +1/width,uv.y}) * u_ratio) * v_opposite 
               + (GetSample((Vec2){uv.x,uv.y+1/height}) * u_opposite  + GetSample((Vec2){uv.x +1/width,uv.y+1/height}) * u_ratio) * v_ratio;
   return result;
 }