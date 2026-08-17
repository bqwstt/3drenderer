#include "vec.h"

#include <math.h>

FVec2 fvec2_zero()
{
    FVec2 result;
    result.x = 0.0f;
    result.y = 0.0f;
    return result;
}

FVec3 fvec3_zero()
{
    FVec3 result;
    result.x = 0.0f;
    result.y = 0.0f;
    result.z = 0.0f;
    return result;
}

FVec2 fvec2_from_point(float x, float y)
{
    FVec2 result;
    result.x = x;
    result.y = y;
    return result;
}

FVec2 fvec2_rotate(FVec2 vec, float angle)
{
    FVec2 result;
    result.x = vec.x * cos(angle) - vec.y * sin(angle);
    result.y = vec.x * sin(angle) + vec.y * cos(angle);
    return result;
}

FVec3 fvec3_from_point(float x, float y, float z)
{
    FVec3 result;
    result.x = x;
    result.y = y;
    result.z = y;
    return result;
}

/// Rotate vectors using rotation matrix
/// References:
/// * https://en.wikipedia.org/wiki/Rotation_matrix
FVec3 fvec3_rotate_x(FVec3 vec, float angle)
{
    FVec3 result;
    result.x = vec.x;
    result.y = vec.y * cos(angle) - vec.z * sin(angle);
    result.z = vec.y * sin(angle) + vec.z * cos(angle);
    return result;
}

FVec3 fvec3_rotate_y(FVec3 vec, float angle)
{
    FVec3 result;
    result.x = vec.x * cos(angle) - vec.z * sin(angle);
    result.y = vec.y;
    result.z = vec.x * sin(angle) + vec.z * cos(angle);
    return result;
}

FVec3 fvec3_rotate_z(FVec3 vec, float angle)
{
    FVec3 result;
    result.x = vec.x * cos(angle) - vec.y * sin(angle);
    result.y = vec.x * sin(angle) + vec.y * cos(angle);
    result.z = vec.z;
    return result;
}