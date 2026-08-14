#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "vec.h"

struct Camera
{
    FVec3 position;
    float32_t fov;
};
typedef struct Camera Camera;

FVec2 orthographic_project_point_to_screen(Camera camera, FVec3 point);
FVec2 perspective_project_point_to_screen(Camera camera, FVec3 point);

#endif // CAMERA_H