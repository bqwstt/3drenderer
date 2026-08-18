#include "model.h"

#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>

#include <stdlib.h>

#include "dyn_array.h"
#include "vec.h"

/// #region Model construction

Model
model_load_from_obj(const char* filename)
{
    Model model;
    model.vertices = dyn_array_make(sizeof(FVec3));
    model.faces = dyn_array_make(sizeof(FVec3));

    size_t data_size;
    char* contents = SDL_LoadFile(filename, &data_size);
    if (contents == NULL) {
        SDL_Log("Couldn't load file from path '%s': %s\n", filename, SDL_GetError());
        return model;
    }

    char* current = contents;
    char* end = contents + data_size;
    while (current < end) {
        char* line_start = current;
        while (current < end && *current != '\n') {
            current++;
        }

        // Parse vertex (v v1 v2 v3)
        size_t line_length = current - line_start;
        if (line_length > 2 && line_start[0] == 'v' && line_start[1] == ' ') {
            FVec3 vertex;
            char* rest;

            vertex.x = strtod(line_start + 2, &rest); // +2 for skipping the beginning we already checked
            vertex.y = -strtod(rest, &rest); // In OBJ, positive Y is our negative Y, so negate it
            vertex.z = strtod(rest, NULL);

            // Add vertex to model
            dyn_array_add(&model.vertices, &vertex);
        }

        // Parse face (f v1[vt1][vn2] v2[vt2][vn2] v3[vt3][vn3])
        if (line_length > 2 && line_start[0] == 'f') {
            FVec3 face;
            char* rest;

            face.x = strtod(line_start + 2, &rest);

            while (*rest != ' ') rest++; // Skip vt (first /) for now.
            face.y = strtod(rest, &rest);

            while (*rest != ' ') rest++; // Skip vn (second /) for now.
            face.z = strtod(rest, NULL);

            // Add face to model
            dyn_array_add(&model.faces, &face);
        }

        // Skip '\n'
        if (current < end && *current == '\n') current++;
    }

    SDL_free(contents);
    return model;
}

/// #region Model drawing

void
draw_3d_model_outline(uint32_t* pixels, Camera camera, Model model, Color color)
{
    for (int i = 0; i < model.faces.length; i++) {
        FVec3* face = dyn_array_get(model.faces, i);
        FVec3* vertex_a = dyn_array_get(model.vertices, (int) face->x-1);
        FVec3* vertex_b = dyn_array_get(model.vertices, (int) face->y-1);
        FVec3* vertex_c = dyn_array_get(model.vertices, (int) face->z-1);

        Triangle triangle;
        triangle.points[0] = *vertex_a;
        triangle.points[1] = *vertex_b;
        triangle.points[2] = *vertex_c;
        draw_3d_triangle_outline_shape(pixels, camera, triangle, color);
    }
}

/// #region Model transforms

void
transform_rotate_3d_model(Model* model, FVec3 rotation)
{
    // Rotate all vertices in the desired axis
    for (int i = 0; i < model->vertices.length; i++) {
        FVec3* vertex = dyn_array_get(model->vertices, i);
        *vertex = fvec3_rotate_x(*vertex, rotation.x);
        *vertex = fvec3_rotate_y(*vertex, rotation.y);
        *vertex = fvec3_rotate_z(*vertex, rotation.z);
    }
}