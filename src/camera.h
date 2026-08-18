#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "vec.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

struct Camera
{
    FVec3 position;
    float32_t fov;
};
typedef struct Camera Camera;

FVec2 orthographic_project_3d_point(Camera camera, FVec3 point);
FVec2 perspective_project_3d_point(Camera camera, FVec3 point);

#endif // CAMERA_H