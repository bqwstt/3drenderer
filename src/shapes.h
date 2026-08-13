#ifndef SHAPES_H
#define SHAPES_H

#include <stdint.h>
#include <stdio.h>

#include "vec.h"

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

/// === Shape definitions ===
struct Rectangle
{
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
};
typedef struct Rectangle Rectangle;

struct Line
{
    uint32_t x0;
    uint32_t y0;
    uint32_t x1;
    uint32_t y1;
};
typedef struct Line Line;

struct Cube
{
    FVec3 points[8];
};
typedef struct Cube Cube;

/// === Drawing functions ===

void draw_2d_point(uint32_t* pixels, uint32_t x, uint32_t y, Color color); /* Draw 2D point using x and y coordinates */
void draw_2d_line_points(uint32_t* pixels, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color); /* Draw 2D line using x and y coordinates */
void draw_2d_line_shape(uint32_t* pixels, Line line, Color color); /* Draw 2D line */
void draw_2d_rectangle_filled_points(uint32_t* pixels, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, Color color);  /* Draw a color-filled 2D rectangle using coordinates */
void draw_2d_rectangle_filled_shape(uint32_t* pixels, Rectangle rect, Color color); /* Draw a color-filled 2D rectangle */
void draw_2d_rectangle_outline_points(uint32_t* pixels, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, Color color); /* Draw 2D rectangle outlines using coordinates */
void draw_2d_rectangle_outline_shape(uint32_t* pixels, Rectangle rect, Color color); /* Draw 2D rectangle outlines */
void draw_3d_cube_shape(uint32_t* pixels, Cube cube, Color color); /* Draw 3D cube */

#endif // SHAPES_H