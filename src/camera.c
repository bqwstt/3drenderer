#include "camera.h"

FVec2
orthographic_project_3d_point(Camera camera, FVec3 point)
{
    FVec2 projected_point;
    projected_point.x = camera.fov * point.x;
    projected_point.y = camera.fov * point.y;
    return projected_point;
}

FVec2
perspective_project_3d_point(Camera camera, FVec3 point)
{
    // @TODO: Implement focal length
    FVec2 projected_point;
    projected_point.x = (camera.fov * point.x) / point.z;
    projected_point.y = (camera.fov * point.y) / point.z;
    return projected_point;
}