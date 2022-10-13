#pragma once

#include <myMath.hpp>
#include <vector>

class Texture
{
private:
    int width;
    int height;
    std::vector<Vec4> pixels;
public:
    Texture(){};
    ~Texture(){pixels.clear();};

    void LoadTexture(const char* fileName);

    int GetWidth() {return width;};
    int GetHeight() {return height;};
    Vec4 GetSample(Vec2 uv);
    Vec4 GetBilinearFilteredPixelColor(Vec2 uv) ;
};