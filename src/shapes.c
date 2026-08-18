#include "utils.h"
#include "shapes.h"

#include <math.h>
#include <stdlib.h>

/// #region Shape defs

Line
make_3d_line(FVec3 from, FVec3 to)
{
    Line line;
    line.from = from;
    line.to = to;
    return line;
}

Plane
make_3d_plane(FVec3 position, float width, float height)
{
    Plane plane;    

    float half_width = width / 2.0;
    float half_height = height / 2.0;

    // Local-space coordinates
    plane.points[0] = (FVec3) { .x = -half_width, .y = -half_height, .z = 0}; // Top left
    plane.points[1] = (FVec3) { .x =  half_width, .y = -half_height, .z = 0}; // Top right
    plane.points[2] = (FVec3) { .x = -half_width, .y =  half_height, .z = 0}; // Bottom left
    plane.points[3] = (FVec3) { .x =  half_width, .y =  half_height, .z = 0}; // Bottom right

    // World-space coordinates
    for (int i = 0; i < 4; i++) {
        // Translate by position 
        plane.points[i].x += position.x;
        plane.points[i].y += position.y;
        plane.points[i].z += position.z;
    }

    return plane;
}

Cube
make_3d_cube(FVec3 position /*, float size */)
{
    Cube cube;

    // @FIXME: This was supposed to be used for scaling, but 
    // may not be exactly what we want... leaving it as 1 for now.
    float half_size = 1.0;

    // Create vertices
    cube.points[0] = (FVec3) { .x = -half_size, .y = -half_size, .z =  half_size}; // (1) Top left, back face
    cube.points[1] = (FVec3) { .x =  half_size, .y = -half_size, .z =  half_size}; // (2) Top right back face
    cube.points[2] = (FVec3) { .x = -half_size, .y =  half_size, .z =  half_size}; // (3) Bottom left, back face
    cube.points[3] = (FVec3) { .x =  half_size, .y =  half_size, .z =  half_size}; // (4) Bottom right, back face
    cube.points[4] = (FVec3) { .x = -half_size, .y = -half_size, .z = -half_size}; // (5) Top left, front face
    cube.points[5] = (FVec3) { .x =  half_size, .y = -half_size, .z = -half_size}; // (6) Top right front face
    cube.points[6] = (FVec3) { .x = -half_size, .y =  half_size, .z = -half_size}; // (7) Bottom left, front face
    cube.points[7] = (FVec3) { .x =  half_size, .y =  half_size, .z = -half_size}; // (8) Bottom right, front face

    for (int i = 0; i < 8; i++) {
        cube.points[i].x += position.x;
        cube.points[i].y += position.y;
        cube.points[i].z += position.z;
    }

    // Connect vertices with edges (using array indexes, starting from 0)
    // Front face edges
    cube.edges[0] = (FVec2) { 0, 1 }; // Top left (B) -> top right (B)
    cube.edges[1] = (FVec2) { 1, 3 }; // Top right (B) -> bottom right (B)
    cube.edges[2] = (FVec2) { 3, 2 }; // Bottom right (B) -> bottom left (B)
    cube.edges[3] = (FVec2) { 2, 0 }; // Bottom left (B) -> top left (B)

    // Back face edges
    cube.edges[4] = (FVec2) { 4, 5 }; // Top left (F) -> top right (F)
    cube.edges[5] = (FVec2) { 5, 7 }; // Top right (F) -> bottom right (F)
    cube.edges[6] = (FVec2) { 7, 6 }; // Bottom right (F) -> bottom left (F)
    cube.edges[7] = (FVec2) { 6, 4 }; // Bottom left (F) -> top left (F)

    // Connect front and back face together with edges
    cube.edges[8] = (FVec2) { 0, 4 }; // Top left (B) -> top left (F)
    cube.edges[9] = (FVec2) { 1, 5 }; // Top right (B) -> top right (F)
    cube.edges[10] = (FVec2) { 2, 6 }; // Bottom left (B) -> bottom left (F)
    cube.edges[11] = (FVec2) { 3, 7 }; // Bottom right (B) -> bottom right (F)

    // Connect (triangular) faces (using face ids, starting from 1)
    cube.faces[0] = (FVec3) { 1, 2, 3 }; // Back (1/2)
    cube.faces[1] = (FVec3) { 2, 4, 3 }; // Back (2/2)
    cube.faces[2] = (FVec3) { 2, 6, 4 }; // Right (1/2)
    cube.faces[3] = (FVec3) { 6, 8, 4 }; // Right (2/2)
    cube.faces[4] = (FVec3) { 5, 7, 6 }; // Front (1/2)
    cube.faces[5] = (FVec3) { 6, 7, 8 }; // Front (2/2)
    cube.faces[6] = (FVec3) { 5, 3, 7 }; // Left (1/2)
    cube.faces[7] = (FVec3) { 3, 1, 5 }; // Left (2/2)
    cube.faces[8] = (FVec3) { 1, 5, 2 }; // Top (1/2)
    cube.faces[9] = (FVec3) { 2, 5, 6 }; // Top (2/2)
    cube.faces[10] = (FVec3) { 3, 4, 7 }; // Bottom (1/2)
    cube.faces[11] = (FVec3) { 4, 8, 7 }; // Bottom (2/2)

    return cube;
}

/// #region 2D drawing

/// Draws a 2D point at (x, y) with `color`
inline void
draw_2d_point(uint32_t* pixels, Camera camera, uint32_t x, uint32_t y, Color color)
{
    uint32_t target_x = x - camera.position.x;
    uint32_t target_y = y - camera.position.y;

    if (target_x >= 0 && target_x < WINDOW_WIDTH && target_y >= 0 && target_y < WINDOW_HEIGHT) {
        pixels[(WINDOW_WIDTH * target_y) + target_x] = color;
    }
}

/// Draws a 2D line to `pixels` using Bresenham's line drawing algorithm
/// References:
/// * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
/// * https://haqr.eu/tinyrenderer/bresenham/
///
/// @TODO: The article above mentions this being inneficient. 
///        Profile and optimize?
void
draw_2d_segment_points(uint32_t* pixels, Camera camera, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color)
{
    // If the line is too steep, and given that we increment by x later, we want
    // to preserve the smooth filling, we can swap x and y together to not lose
    // pixels on the way
    //
    //     * │          * │      Notice the extra space when on the x-axis,
    //       │y        *  │x     these get eliminated once we iterate over y.
    //    *  │'        *  │'     Think of rotating the screen when filling.
    //       │a       *   │a
    //   *   │x ───>  *   │x
    //       │i      *    │i
    //  *    │s      *    │s
    //  ─────┘       ─────┘
    //  x-axis       y-axis
    int32_t ax = x0;
    int32_t bx = x1;
    int32_t ay = y0;
    int32_t by = y1;

    bool_t steep = abs(ax - bx) < abs(ay - by);
    if (steep) {
        swap(ax, ay);
        swap(bx, by);
    }

    // Our loop goes from x0-->x1, which assumes we're going from left to right.
    // In case that we're starting from the right, we have to swap these points.
    if (ax > bx) {
        swap(ax, bx);
        swap(ay, by);
    }

    // @TODO: Understand the ierror thing?
    // The Bresenham's line drawing algorithm article uses all integers
    // instead of floats for performance reasons, but in our case it also
    // fixes a couple of bugs related to precision and/or representation.
    // I'm keeping the integer-only approach as it works but I don't really
    // understand it.
    int32_t y = ay;
    int32_t ierror = 0;

    for (int x = ax; x <= bx; x++) {
        if (steep) {
            // If transposed, de-transpose
            draw_2d_point(pixels, camera, y, x, color);
        } else {
            draw_2d_point(pixels, camera, x, y, color);
        }

        ierror += 2 * abs(by-ay);
        if (ierror > (bx - ax)) {
            y += by > ay ? 1 : -1;
            ierror -= 2 * (bx - ax);
        }
    }
}

/// Draws a 2D line `line` with `color`
/// Uses Bresenham's algorithm for rendering. See `draw_2d_line_points()`
inline void
draw_2d_segment_shape(uint32_t* pixels, Camera camera, Segment segment, Color color)
{
    draw_2d_segment_points(pixels, camera, segment.x0, segment.y0, segment.x1, segment.y1, color);
}

/// Draws and fills a 2D rectangle at (x, y, x + width, y + width) with `color`
/// Note that as the rectangle is filled with `color`, we can just iterate over pixels
/// and draw directly to them, without having to use lines.
void
draw_2d_rectangle_filled_points(uint32_t* pixels,
                      Camera camera,
                      uint32_t x, uint32_t y,
                      uint32_t width, uint32_t height,
                      Color color)
{
    for (uint32_t py = y; py < y + height; py++) {
        for (uint32_t px = x; px < x + width; px++) {
            draw_2d_point(pixels, camera, px, py, color);
        }
    }
}

/// Draws and fills a 2D rectangle `rect` with `color`
inline void
draw_2d_rectangle_filled_shape(uint32_t* pixels, Camera camera, Rectangle rect, Color color)
{
    draw_2d_rectangle_filled_points(pixels, camera, rect.x, rect.y, rect.width, rect.height, color);
}

/// Draws the outline of a 2D rectangle at (x, y, x + width, y + height) with `color`-ed lines
void
draw_2d_rectangle_outline_points(uint32_t* pixels,
                                 Camera camera,
                                 uint32_t x, uint32_t y,
                                 uint32_t width, uint32_t height,
                                 Color color)
{
    draw_2d_segment_points(pixels, camera, x, y, x + width, y, color);
    draw_2d_segment_points(pixels, camera, x + width, y, x + width, y + height, color);
    draw_2d_segment_points(pixels, camera, x + width, y + height, x, y + height, color);
    draw_2d_segment_points(pixels, camera, x, y + height, x, y, color);
}

/// Draws the outline of a 2D rectangle `rect` with `color`-ed lines
inline void
draw_2d_rectangle_outline_shape(uint32_t* pixels, Camera camera, Rectangle rect, Color color)
{
    draw_2d_rectangle_outline_points(pixels, camera, rect.x, rect.y, rect.width, rect.height, color);
}

/// #region 3D drawing

/// Projects and draws a 3D line (2D `Segment` -> 3D `Line`)
void
draw_3d_line_shape(uint32_t* pixels, Camera camera, Line line, Color color)
{
    FVec2 projected_points[2];
    for (int i = 0; i < 2; i++) {
        FVec3 point = line.points[i];
        point.x -= camera.position.x;
        point.y -= camera.position.y;
        point.z -= camera.position.z;

        projected_points[i] = perspective_project_3d_point(camera, point);
        // @DEBUG: Put it in the middle of the screen
        // This changes the vanishing point
        projected_points[i].x += (float) WINDOW_WIDTH / 2;
        projected_points[i].y += (float) WINDOW_HEIGHT / 2;
    }

    FVec2 from = projected_points[0];
    FVec2 to = projected_points[1];

    draw_2d_segment_points(
        pixels,
        camera,
        from.x, from.y,
        to.x, to.y,
        color
    );
}

/// Projects and draws a 3D plane (2D `Rectangle` -> 3D `Plane`)
void
draw_3d_plane_shape(uint32_t* pixels, Camera camera, Plane plane, Color color)
{
    FVec2 projected_points[4];
    for (int i = 0; i < 4; i++) {
        FVec3 point = plane.points[i];
        point.x -= camera.position.x;
        point.y -= camera.position.y;
        point.z -= camera.position.z;

        projected_points[i] = perspective_project_3d_point(camera, point);
        // @DEBUG: Put it in the middle of the screen
        // This changes the vanishing point
        projected_points[i].x += (float) WINDOW_WIDTH / 2;
        projected_points[i].y += (float) WINDOW_HEIGHT / 2;
    }

    FVec2 top_left = projected_points[0];
    FVec2 bottom_right = projected_points[3];
    uint32_t width = bottom_right.x - top_left.x;
    uint32_t height = bottom_right.y - top_left.y;

    // @TODO: Check if it's rotated. In that case, we need to use a different algorithm.
    draw_2d_rectangle_filled_points(
        pixels,
        camera,
        top_left.x, top_left.y,
        width, height,
        color
    );
}

/// Projects and draws a 3D triangle
void
draw_3d_triangle_shape(uint32_t* pixels, Camera camera, Triangle triangle, Color color)
{
    FVec2 projected_points[3];
    for (int i = 0; i < 3; i++) {
        FVec3 point = triangle.points[i];
        point.x -= camera.position.x;
        point.y -= camera.position.y;
        point.z -= camera.position.z;

        FVec2 projected_point = perspective_project_3d_point(camera, point);
        // @DEBUG: Put it in the middle of the screen
        // This changes the vanishing point
        projected_point.x += (float) WINDOW_WIDTH / 2;
        projected_point.y += (float) WINDOW_HEIGHT / 2;
        projected_points[i] = projected_point;
    }

    // A -> B
    draw_2d_segment_points(
        pixels,
        camera,
        projected_points[0].x, projected_points[0].y,
        projected_points[1].x, projected_points[1].y,
        color
    );
    // B -> C
    draw_2d_segment_points(
        pixels,
        camera,
        projected_points[1].x, projected_points[1].y,
        projected_points[2].x, projected_points[2].y,
        color
    );

    // C -> A
    draw_2d_segment_points(
        pixels,
        camera,
        projected_points[2].x, projected_points[2].y,
        projected_points[0].x, projected_points[0].y,
        color
    );
}

/// Projects and draws a 3D cube
void
draw_3d_cube_shape(uint32_t* pixels, Camera camera, Cube cube, Color color)
{
    // Draw wireframe by connecting vertices with lines
    for (int i = 0; i < countof(cube.edges); i++) {
        FVec2 line_coords = cube.edges[i];
        FVec3 from_point = cube.points[(int) line_coords.x];
        FVec3 to_point = cube.points[(int) line_coords.y];

        Line line = make_3d_line(from_point, to_point);
        draw_3d_line_shape(pixels, camera, line, color);
    }

    for (int i = 0; i < countof(cube.faces); i++) {
        FVec3 face = cube.faces[i];
        Triangle triangle;
        triangle.points[0] = cube.points[(int) face.x-1];
        triangle.points[1] = cube.points[(int) face.y-1];
        triangle.points[2] = cube.points[(int) face.z-1];
        draw_3d_triangle_shape(pixels, camera, triangle, color);
    }
}

/// #region Transforms

/// Rotates a `Segment` by `angle` radians
void
transform_rotate_2d_segment(Segment* segment, float angle)
{
    // @TODO: make rotation possible from the center of the line?
    // Right now it rotates from the start.
    uint32_t dx = segment->x1 - segment->x0;
    uint32_t dy = segment->y1 - segment->y0;
    segment->x1 = segment->x0 + cos(angle) * dx - sin(angle) * dy;
    segment->y1 = segment->y0 + sin(angle) * dx + cos(angle) * dy;
}

/// Rotates a `Cube` with `rotation` radians (in all x, y and z)
void
transform_rotate_3d_cube(Cube* cube, FVec3 rotation)
{
    // Rotate all points in the desired axis
    for (int i = 0; i < countof(cube->points); i++) {
        FVec3 point = cube->points[i];
        point = fvec3_rotate_x(point, rotation.x);
        point = fvec3_rotate_y(point, rotation.y);
        point = fvec3_rotate_z(point, rotation.z);
        cube->points[i] = point;
    }
}