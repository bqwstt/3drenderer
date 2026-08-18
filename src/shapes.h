#ifndef SHAPES_H
#define SHAPES_H

#include <stdint.h>
#include <stdio.h>

#include "vec.h"
#include "camera.h"

// @TODO: Move these
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

// Using ARGB8888 format
typedef uint32_t Color;
#define COLOR_BLACK     (Color) 0xFF000000
#define COLOR_WHITE     (Color) 0xFFFFFFFF
#define COLOR_RED       (Color) 0xFFFF0000
#define COLOR_GREEN     (Color) 0xFF00FF00
#define COLOR_BLUE      (Color) 0xFF0000FF
#define COLOR_CYAN      (Color) 0xFF00FFFF
#define COLOR_YELLOW    (Color) 0xFFFFFF00
#define COLOR_MAGENTA   (Color) 0xFFFF00FF
#define COLOR_GRAY      (Color) 0xFF808080
#define COLOR_LIGHTGRAY (Color) 0xFF333333
#define COLOR_ORANGE    (Color) 0xFFFF8000
#define COLOR_PURPLE    (Color) 0xFF8000FF
#define COLOR_PINK      (Color) 0xFFFF80C0
#define COLOR_BROWN     (Color) 0xFF804000

/// #region 2D shape definitions

struct Rectangle
{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};
typedef struct Rectangle Rectangle;

struct Triangle
{
    FVec3 points[3];
};
typedef struct Triangle Triangle;

/// 2D line
struct Segment
{
    uint32_t x0;
    uint32_t y0;
    uint32_t x1;
    uint32_t y1;
};
typedef struct Segment Segment;

/// #region 3D shape definitions

/// @TODO: Revisit usage of floats. Maybe we should use ints?
struct Line
{
    union {
        struct {
            FVec3 from;
            FVec3 to;
        };
        FVec3 points[2];
    };
};
typedef struct Line Line;

struct Plane
{
    union {
        struct {
            FVec3 top_left;
            FVec3 top_right;
            FVec3 bottom_left;
            FVec3 bottom_right;
        };
        FVec3 points[4];
    };
};
typedef struct Plane Plane;

struct Cube
{
    FVec3 points[8];
    FVec2 edges[12];
    FVec3 faces[12];
};
typedef struct Cube Cube;

/// #region Creation functions

Line make_3d_line(FVec3 from, FVec3 to);
Plane make_3d_plane(FVec3 position, float width, float height);
Cube make_3d_cube(FVec3 position /*, float size */);

/// #region Drawing functions

void draw_2d_point(uint32_t* pixels, Camera camera, uint32_t x, uint32_t y, Color color); /* Draw 2D point using x and y coordinates */
void draw_2d_segment_points(uint32_t* pixels, Camera camera, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color); /* Draw 2D segment (line) using x and y coordinates */
void draw_2d_segment_shape(uint32_t* pixels, Camera camera, Segment segment, Color color); /* Draw 2D segment (line) */
void draw_2d_rectangle_filled_points(uint32_t* pixels, Camera camera, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, Color color);  /* Draw a color-filled 2D rectangle using coordinates */
void draw_2d_rectangle_filled_shape(uint32_t* pixels, Camera camera, Rectangle rect, Color color); /* Draw a color-filled 2D rectangle */
void draw_2d_rectangle_outline_points(uint32_t* pixels, Camera camera, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, Color color); /* Draw 2D rectangle outlines using coordinates */
void draw_2d_rectangle_outline_shape(uint32_t* pixels, Camera camera, Rectangle rect, Color color); /* Draw 2D rectangle outlines */

void draw_3d_line_shape(uint32_t* pixels, Camera camera, Line line, Color color); /* Draw 3D line */
void draw_3d_plane_outline_shape(uint32_t* pixels, Camera camera, Plane plane, Color color); /* Draw 3D rectangle (or "plane") */
void draw_3d_triangle_outline_shape(uint32_t* pixels, Camera camera, Triangle triangle, Color color); /* Draw 3D triangle */
void draw_3d_cube_outline_shape(uint32_t* pixels, Camera camera, Cube cube, Color color); /* Draw 3D cube */

/// #region Transformation functions

// @TODO: Separate drawing from transforming?
// If we turn this into a library, people can maybe just use "draw_*" functions
// to draw and handle transformations themselves.
void transform_rotate_2d_segment(Segment* segment, float angle);
void transform_rotate_3d_cube(Cube* cube, FVec3 rotation);

#endif // SHAPES_H