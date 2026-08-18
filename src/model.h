#ifndef MODEL_H
#define MODEL_H

#include "dyn_array.h"

struct Model
{
    Dyn_Array vertices;
    Dyn_Array faces;
};
typedef struct Model Model;

/// Model loader
Model model_load_from_obj(const char* filename); /* Load a model from an .obj file */

#endif // MODEL_H