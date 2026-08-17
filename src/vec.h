#ifndef VEC_H
#define VEC_H

#include "utils.h"

struct FVec2
{
    float32_t x;
    float32_t y;
};
typedef struct FVec2 FVec2;

struct IVec2
{
    int32_t x;
    int32_t y;
};
typedef struct IVec2 IVec2;

struct IVec3
{
    int32_t x;
    int32_t y;
    int32_t z;
};
typedef struct IVec3 IVec3;

struct UVec2
{
    uint32_t x;
    uint32_t y;
};
typedef struct UVec2 UVec2;

struct UVec3
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
};
typedef struct UVec3 UVec3;

struct FVec3
{
    float32_t x;
    float32_t y;
    float32_t z;
};
typedef struct FVec3 FVec3;

FVec2 fvec2_zero();
FVec3 fvec3_zero();

FVec2 fvec2_from_point(float x, float y);
FVec2 fvec2_rotate(FVec2 vec, float angle);

FVec3 fvec3_from_point(float x, float y, float z);
FVec3 fvec3_rotate_x(FVec3 vec, float angle);
FVec3 fvec3_rotate_y(FVec3 vec, float angle);
FVec3 fvec3_rotate_z(FVec3 vec, float angle);

#endif // VEC_H