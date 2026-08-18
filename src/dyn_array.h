#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <stddef.h>

struct Dyn_Array
{
    void* data;
    size_t capacity;
    size_t length;
    size_t element_size;
};
typedef struct Dyn_Array Dyn_Array;

// @TODO: Optimize, maybe be able to pass in a capacity in a separate function?
Dyn_Array dyn_array_make(size_t element_size); /* Initialize a dynamic array with a single element @Allocates */
void dyn_array_add(Dyn_Array* array, const void* element); /* Adds an element to an existing array @Allocates */
void* dyn_array_get(Dyn_Array array, size_t index); /* Returns the `index`th element in the array */
void dyn_array_drop(Dyn_Array* array); /* Cleans and deallocates an array */

#endif // DYN_ARRAY_H