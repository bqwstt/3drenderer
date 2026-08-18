#ifndef MODEL_H
#define MODEL_H

#include "shapes.h"
#include "utils.h"
#include "camera.h"
#include "dyn_array.h"

struct Model
{
    Dyn_Array vertices;
    Dyn_Array faces;
};
typedef struct Model Model;

/// Model loader
Model model_load_from_obj(const char* filename); /* Load a model from an .obj file */

/// #region Drawing functions

void draw_3d_model_outline(uint32_t* pixels, Camera camera, Model model, Color color);

/// #region Transformation functions

void transform_rotate_3d_model(Model* model, FVec3 rotation);

#endif // MODEL_H