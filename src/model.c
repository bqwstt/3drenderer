#include "model.h"

#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>

#include <stdlib.h>

#include "dyn_array.h"
#include "vec.h"

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
            vertex.y = strtod(rest, &rest);
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