#include "shapes.h"

/// Draws a 2D point at (x, y) with `color`
inline void
draw_2d_point(uint32_t* pixels, uint32_t x, uint32_t y, Color color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        pixels[(WINDOW_WIDTH * y) + x] = color;
    }
}

/// Draws a 2D rectangle at (x0, y0, x0 + width, y0 + width) with `color`
void
draw_2d_rectangle_points(uint32_t* pixels,
                      uint32_t x, uint32_t y,
                      uint32_t width, uint32_t height,
                      Color color)
{
    for (uint32_t py = y; py < y + height; py++) {
        for (uint32_t px = x; px < x + width; px++) {
            draw_2d_point(pixels, px, py, color);
        }
    }
}

/// Draws a 2D rectangle `rect` with `color`
inline void
draw_2d_rectangle_shape(uint32_t* pixels, Rectangle rect, Color color)
{
    draw_2d_rectangle_points(pixels, rect.x, rect.y, rect.width, rect.height, color);
}

/// Draws a 2D line to `pixels` using Bresenham's line drawing algorithm
/// References:
/// * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
/// * https://haqr.eu/tinyrenderer/bresenham/
void
draw_2d_line_points(uint32_t* pixels, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color)
{
    todo("Implement draw_2d_line_points");
}

/// Draws a 2D line `line` with `color`
/// Uses Bresenham's algorithm for rendering. See `draw_2d_line_points()`
void
draw_2d_line_shape(uint32_t* pixels, Line line, Color color)
{
    todo("Implement draw_2d_line_shape");
}

void
draw_3d_cube_shape(uint32_t* pixels, Cube cube, Color color)
{
    todo("Implement draw_3d_cube_shape");
}