#include "utils.h"
#include "shapes.h"

#include <math.h>

/// Draws a 2D point at (x, y) with `color`
inline void
draw_2d_point(uint32_t* pixels, uint32_t x, uint32_t y, Color color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        pixels[(WINDOW_WIDTH * y) + x] = color;
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
draw_2d_line_points(uint32_t* pixels, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, Color color)
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
    bool_t steep = (x0-x1) < (y0-y1);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    // Our loop goes from x0-->x1, which assumes we're going from left to right.
    // In case that we're starting from the right, we have to swap these points.
    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++) {
        float t = (x-x0) / (float)(x1-x0);
        int y = round(y0 + (y1-y0) * t);
        if (steep) {
            // Transpose the line
            draw_2d_point(pixels, y, x, color);
        } else {
            draw_2d_point(pixels, x, y, color);
        }
    }
}

/// Draws a 2D line `line` with `color`
/// Uses Bresenham's algorithm for rendering. See `draw_2d_line_points()`
inline void
draw_2d_line_shape(uint32_t* pixels, Line line, Color color)
{
    draw_2d_line_points(pixels, line.x0, line.y0, line.x1, line.y0, color);
}

/// Draws and fills a 2D rectangle at (x, y, x + width, y + width) with `color`
/// Note that as the rectangle is filled with `color`, we can just iterate over pixels
/// and draw directly to them, without having to use lines.
void
draw_2d_rectangle_filled_points(uint32_t* pixels,
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

/// Draws and fills a 2D rectangle `rect` with `color`
inline void
draw_2d_rectangle_filled_shape(uint32_t* pixels, Rectangle rect, Color color)
{
    draw_2d_rectangle_filled_points(pixels, rect.x, rect.y, rect.width, rect.height, color);
}

/// Draws the outline of a 2D rectangle at (x, y, x + width, y + height) with `color`-ed lines
void
draw_2d_rectangle_outline_points(uint32_t* pixels,
                                 uint32_t x, uint32_t y,
                                 uint32_t width, uint32_t height,
                                 Color color)
{
    draw_2d_line_points(pixels, x, y, x + width, y, color);
    draw_2d_line_points(pixels, x + width, y, x + width, y + height, color);
    draw_2d_line_points(pixels, x + width, y + height, x, y + height, color);
    draw_2d_line_points(pixels, x, y + height, x, y, color);
}

/// Draws the outline of a 2D rectangle `rect` with `color`-ed lines
inline void
draw_2d_rectangle_outline_shape(uint32_t* pixels, Rectangle rect, Color color)
{
    draw_2d_rectangle_outline_points(pixels, rect.x, rect.y, rect.width, rect.height, color);
}

void
draw_3d_cube_shape(uint32_t* pixels, Cube cube, Color color)
{
    todo("Implement draw_3d_cube_shape");
}