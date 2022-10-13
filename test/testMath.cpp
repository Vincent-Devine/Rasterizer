#include <iostream>
#include "../third_party/glm/mat4x4.hpp"
#include "../third_party/glm/vec2.hpp"
#include "../third_party/glm/vec3.hpp"
#include "../third_party/glm/vec4.hpp"
#include "../third_party/glm/gtc/matrix_transform.hpp"
#include "myMath.hpp"

/////////////////////////////

Mat4 GlmMatToMat(const glm::mat4x4& mat)
{
    return Mat4(mat[0][0], mat[1][0], mat[2][0], mat[3][0], 
                mat[0][1], mat[1][1], mat[2][1], mat[3][1],
                mat[0][2], mat[1][2], mat[2][2], mat[3][2],
                mat[0][3], mat[1][3], mat[2][3], mat[3][3]);
}

////////////////////////////

// ----------------------------------------------------------------------------------
// -------------------------------------- Vec2 --------------------------------------
// ----------------------------------------------------------------------------------

bool testVec2Operator()
{
    Vec2 v1(1.f, 1.f);
    Vec2 v2(1.f, 1.f);

    // Operator +
    if (v1 + v2 != (Vec2){2.f, 2.f})
        return false;
    // Operator +=
    v1 += v2;
    if (v1 != (Vec2){2.f, 2.f})
        return false;
    // Operator -
    if (v1 - v2 != (Vec2){1.f, 1.f})
        return false;
    // Operator -=
    v1 -= v2;
    if (v1 != (Vec2){1.f, 1.f})
        return false;
    // Operator *
    if (v1 * 2 != (Vec2){2.f, 2.f})
        return false;
    // Operator *=
    v1 *= 2;
    if (v1 != (Vec2){2.f, 2.f})
        return false;
    // Operator /
    if (v1 / 2 != (Vec2){1.f, 1.f})
        return false;
    // Operator /=
    v1 /= 2;
    if (v1 != (Vec2){1.f, 1.f})
        return false;
    // Operator <
    if (v1 < (Vec2){0.9f, 0.9f})
        return false;
    // Operator >
    if (v1 > (Vec2){1.1f, 1.1f})
        return false;
    // Operator <=
    if (!(v1 <= (Vec2){1.0f, 1.0f}))
        return false;
    // Operator >=
    if (!(v1 >= (Vec2){1.0f, 1.0f}))
        return false;
    // Operator ==
    if (v1 == v2)
        return true;
    return false;
}

void display(Vec3 vec)
{
    std::cout << "[ " << vec.x << ", " << vec.y << ", " << vec.z << " ]" << std::endl;
}

void display(Vec4 vec)
{
    std::cout << "[ " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " ]" << std::endl;
}

void display(Mat4 matrix)
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix.mat[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void display(glm::mat4 matrix)
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

bool testVec2DotProduct()
{
    Vec2 v1(1.f, 4.f);
    Vec2 v2(2.f, 3.f);
    glm::vec2 v3(1.f, 4.f);
    glm::vec2 v4(2.f, 3.f);

    if (v1.DotProduct(v2) == glm::dot(v3, v4))
        return true;
    return false;
}

bool testVec2Magnitude()
{
    Vec2 v1(4.f, 4.f);
    glm::vec2 v2(4.f, 4.f);
    if (v1.Magnitude() == glm::length(v2))
        return true;
    return false;
}
bool testVec2CrossProduct()
{
    Vec2 v1(5.f, 4.f);
    Vec2 v2(2.f, 3.f);
    if (v1.CrossProduct(v2) == 7)
        return true;
    return false;
}

bool testVec2Normalize()
{
    Vec2 v1(4.f, 4.f);
    glm::vec2 v2(4.f, 4.f);
    float magnitude = v1.Magnitude();
    v1.Normalize();
    if (v1.x == glm::normalize(v2).x && v1.y == glm::normalize(v2).y)
        return true;
    return false;
}

bool testVec2()
{
    if (testVec2Operator() && testVec2DotProduct() && testVec2Magnitude() && testVec2CrossProduct() && testVec2Normalize())
        return true;
    return false;
}

// ----------------------------------------------------------------------------------
// -------------------------------------- Vec3 --------------------------------------
// ----------------------------------------------------------------------------------

bool testVec3Operator()
{
    Vec3 v1(1.f, 1.f, 1.f);
    Vec3 v2(1.f, 1.f, 1.f);

    // Operator +
    if (v1 + v2 != (Vec3){2.f, 2.f, 2.f})
        return false;
    // Operator +=
    v1 += v2;
    if (v1 != (Vec3){2.f, 2.f, 2.f})
        return false;
    // Operator -
    if (v1 - v2 != (Vec3){1.f, 1.f, 1.f})
        return false;
    // Operator -=
    v1 -= v2;
    if (v1 != (Vec3){1.f, 1.f, 1.f})
        return false;
    // Operator *
    if (v1 * 2 != (Vec3){2.f, 2.f, 2.f})
        return false;
    // Operator *=
    v1 *= 2;
    if (v1 != (Vec3){2.f, 2.f, 2.f})
        return false;
    // Operator /
    if (v1 / 2 != (Vec3){1.f, 1.f, 1.f})
        return false;
    // Operator /=
    v1 /= 2;
    if (v1 != (Vec3){1.f, 1.f, 1.f})
        return false;
    // Operator <
    if (v1 < (Vec3){0.9f, 0.9f, 0.9f})
        return false;
    // Operator >
    if (v1 > (Vec3){1.1f, 1.1f, 1.1f})
        return false;
    // Operator <=
    if (!(v1 <= (Vec3){1.0f, 1.0f, 1.0f}))
        return false;
    // Operator >=
    if (!(v1 >= (Vec3){1.0f, 1.0f, 1.0f}))
        return false;
    // Operator ==
    if (v1 == v2)
        return true;
    return false;
}

bool testVec3DotProduct()
{
    Vec3 v1(2.f, 2.f, 2.f);
    Vec3 v2(3.f, 3.f, 3.f);
    glm::vec3 v3(2.f, 2.f, 2.f);
    glm::vec3 v4(3.f, 3.f, 3.f);
    if (v1.DotProduct(v2) == glm::dot(v3, v4))
        return true;
    return false;
}

bool testVec3Magnitude()
{
    Vec3 v1(2.f, 2.f, 2.f);
    glm::vec3 v2(2.f, 2.f, 2.f);
    if (v1.Magnitude() == glm::length(v2))
        return true;
    return false;
}

bool testVec3CrossProduct()
{
    Vec3 v1(2.f, 2.f, 2.f);
    Vec3 v2(3.f, 3.f, 3.f);

    glm::vec3 v3(2.f, 2.f, 2.f);
    glm::vec3 v4(3.f, 3.f, 3.f);

    if (v1.CrossProduct(v2) == (Vec3){glm::cross(v3, v4).x, glm::cross(v3, v4).y, glm::cross(v3, v4).z})
        return true;
    return false;
}

bool testVec3Normalize()
{
    Vec3 v1(4.f, 4.f, 4.f);
    glm::vec3 v2(4.f, 4.f, 4.f);
    v1.Normalize();
    if (v1.x == glm::normalize(v2).x && v1.y == glm::normalize(v2).y)
        return true;
    return false;
}

bool testVec3()
{
    if (!testVec3Operator())
        return false;
    if (!testVec3DotProduct())
        return false;
    if (!testVec3Magnitude())
        return false;
    if (!testVec3CrossProduct())
        return false;
    if (!testVec3Normalize())
        return false;
    return true;
}

// ----------------------------------------------------------------------------------
// -------------------------------------- Vec4 --------------------------------------
// ----------------------------------------------------------------------------------


bool testVec4Operator()
{
    Vec4 v1(1.f, 1.f, 1.f, 1.f);
    Vec4 v2(1.f, 1.f, 1.f, 1.f);

    // Operator +
    if (v1 + v2 != (Vec4){2.f, 2.f, 2.f, 2.f})
        return false;
    // Operator +=
    v1 += v2;
    if (v1 != (Vec4){2.f, 2.f, 2.f, 2.f})
        return false;
    // Operator -
    if (v1 - v2 != (Vec4){1.f, 1.f, 1.f, 1.f})
        return false;
    // Operator -=
    v1 -= v2;
    if (v1 != (Vec4){1.f, 1.f, 1.f, 1.f})
        return false;
    // Operator *
    if (v1 * 2 != (Vec4){2.f, 2.f, 2.f, 2.f})
        return false;
    // Operator *=
    v1 *= 2;
    if (v1 != (Vec4){2.f, 2.f, 2.f, 2.f})
        return false;
    // Operator /
    if (v1 / 2 != (Vec4){1.f, 1.f, 1.f, 1.f})
        return false;
    // Operator /=
    v1 /= 2;
    if (v1 != (Vec4){1.f, 1.f, 1.f, 1.f})
        return false;
    // Operator <
    if (v1 < (Vec4){0.9f, 0.9f, 0.9f, 0.9f})
        return false;
    // Operator >
    if (v1 > (Vec4){1.1f, 1.1f, 1.1f, 1.1f})
        return false;
    // Operator <=
    if (!(v1 <= (Vec4){1.0f, 1.0f, 1.0f, 1.0f}))
        return false;
    // Operator >=
    if (!(v1 >= (Vec4){1.0f, 1.0f, 1.0f, 1.f}))
        return false;
    // Operator ==
    if (v1 == v2)
        return true;
    return false;
}

bool testVec4DotProduct()
{
    Vec4 v1(2.f, 2.f, 2.f, 2.f);
    Vec4 v2(3.f, 3.f, 3.f, 3.f);
    glm::vec4 v3(2.f, 2.f, 2.f, 2.f);
    glm::vec4 v4(3.f, 3.f, 3.f, 3.f);

    if (v1.DotProduct(v2) == glm::dot(v3, v4))
        return true;
    return false;
}

bool testVec4Magnitude()
{
    Vec4 v1(2.f, 2.f, 2.f, 2.f);
    glm::vec4 v2(2.f, 2.f, 2.f, 2.f);
    if (v1.Magnitude() == glm::length(v2))
        return true;
    return false;
}

bool testVec4Normalize()
{
    Vec4 v1(4.f, 4.f, 4.f, 4.f);
    glm::vec4 v2(4.f, 4.f, 4.f, 4.f);
    float magnitude = v1.Magnitude();
    v1.Normalize();
    if (v1.x == glm::normalize(v2).x && v1.y == glm::normalize(v2).y && v1.z == glm::normalize(v2).z && v1.w == glm::normalize(v2).w)
        return true;
    return false;
}

bool testVec4Homogenize()
{
    Vec4 v1(4.f, 4.f, 4.f, 2.f);
    v1.Homogenize();
    if (v1.x == 2 && v1.y == 2 && v1.z == 2)
        return true;
    return false;
}

bool testVec4()
{
    if (testVec4Operator() && testVec4DotProduct() && testVec4Magnitude() && testVec4Normalize() && testVec4Homogenize())
        return true;
    return false;
}

// ----------------------------------------------------------------------------------
// -------------------------------------- Mat4 --------------------------------------
// ----------------------------------------------------------------------------------

bool testMat4Translation()
{
    Mat4 testMat;
    glm::mat4 test = glm::mat4(1.f);
    Vec3 v3 (4.f, 2.f, 5.f);
    glm ::vec3 vec3(4.f, 2.f, 5.f);
    if((Mat4::CreateTranslationMatrix(v3)) == GlmMatToMat(glm:: translate(test, vec3)))
        return true;
    return false;
}
void matricesTests()
{
    glm::mat4 test = glm::mat4(1.f);
    display(test);

    Mat4 identityMat;
    identityMat = Mat4::Identity();
    display(identityMat);
    Mat4 testMat;
    testMat.mat[0][0] = 1.f; testMat.mat[0][1] = 2.f; testMat.mat[0][2] = 3.f; testMat.mat[0][3] = 4.f;
    testMat.mat[1][0] = 1.f; testMat.mat[1][1] = 2.f; testMat.mat[1][2] = 3.f; testMat.mat[1][3] = 4.f;
    testMat.mat[2][0] = 1.f; testMat.mat[2][1] = 2.f; testMat.mat[2][2] = 3.f; testMat.mat[2][3] = 4.f;
    testMat.mat[3][0] = 1.f; testMat.mat[3][1] = 2.f; testMat.mat[3][2] = 3.f; testMat.mat[3][3] = 4.f;
    display(testMat);
    Mat4 res = identityMat + testMat;
    res = res * testMat;
    display(res);
    res.Transpose();
    display(res);
    testMat4Translation();
}

bool TestMat4XRotation()
{
    Mat4 mat (1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f, 4.f, 4.f, 4.f, 4.f);
    glm::mat4x4 matGlm (1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f);
    if((mat * Mat4::CreateXRotationMatrix(90.f)) == GlmMatToMat(glm::rotate(matGlm, (float)M_PI_2, {1.f, 0.f, 0.f})))
        return true;
    return false;
}

bool TestMat4YRotation()
{
    Mat4 mat (1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f, 4.f, 4.f, 4.f, 4.f);
    glm::mat4x4 matGlm (1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f);
    if((mat * Mat4::CreateYRotationMatrix(90.f)) == GlmMatToMat(glm::rotate(matGlm, (float)M_PI_2, {0.f, 1.f, 0.f})))
        return true;
    return false;
}

bool TestMat4ZRotation()
{
    Mat4 mat (1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f, 4.f, 4.f, 4.f, 4.f);
    glm::mat4x4 matGlm (1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f);
    if((mat * Mat4::CreateZRotationMatrix(90.f)) == GlmMatToMat(glm::rotate(matGlm, (float)M_PI_2, {0.f, 0.f, 1.f})))
        return true;
    return false;}

bool TestMat4Scale()
{
    Mat4 mat (1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 3.f, 3.f, 3.f, 3.f, 4.f, 4.f, 4.f, 4.f);
    glm::mat4x4 matGlm (1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f, 1.f, 2.f, 3.f, 4.f);
    Vec3 scale(2.f, 2.f, 2.f);
    glm::vec3 scaleGlm(2.f, 2.f, 2.f);
    if((mat * Mat4::CreateScaleMatrix(scale)) == GlmMatToMat(glm::scale(matGlm, scaleGlm)))
        return true;
    return false;
}

bool testMat4()
{
    if (TestMat4XRotation() && TestMat4YRotation() && TestMat4ZRotation() && TestMat4Scale() && testMat4Translation())
        return true;
    return false;
}

bool testMat4Operator()
{
    Mat4 mat1 (1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f);
    Mat4 mat2 (1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f);
    Vec4 vec (2.f,2.f,2.f,2.f);

    // Operator ==
    if (mat1 == mat2)
        return true;
    // Operator +
    if (!(mat1 + mat2 == (Mat4){2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f}))
        return false;
    // Operator -
    if (!(mat1 - mat2 == (Mat4){1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f}))
        return false;
        // Operator -
    if (!(mat1 * mat2 == (Mat4){1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f}))
        return false; 
    // Operator *
    if (!(mat1 * vec == (Vec4){2.f, 2.f, 2.f, 2.f}))
        return false;
    return false;

    Mat4 detTest = Mat4(1.f,  2.f,  3.f,  4.f,
                        2.f,  3.f,  4.f,  1.f,
                        3.f,  4.f,  1.f,  2.f,
                        4.f,  1.f,  2.f,  3.f);
    std::cout << "Det: " << detTest.Determinant() << std::endl;

    Mat4 CofTest = Mat4(detTest.CofactorMatrix());
    display(CofTest);

    detTest.Inverse();

    display(detTest);
}
 
int main()
{
    std::cout << "----- Test -----" << std::endl;
    if (testVec2())
        std::cout << "test Vec2 : True" << std::endl;
    else
        std::cout << "test Vec2 : False" << std::endl;
    if (testVec3())
        std::cout << "test Vec3 : True" << std::endl;
    else
        std::cout << "test Vec3 : False" << std::endl;
    if (testVec4())
        std::cout << "test Vec4 : True" << std::endl;
    else
        std::cout << "test Vec4 : False" << std::endl;
    if (testMat4())
        std::cout << "test Mat4 : True" << std::endl;
    else
        std::cout << "test Mat4 : False" << std::endl;

    // matricesTests();
}
