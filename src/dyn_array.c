#include "dyn_array.h"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_log.h>

Dyn_Array
dyn_array_make(size_t element_size)
{
    Dyn_Array array;
    array.data = NULL;

    void* data = SDL_malloc(element_size);
    if (data == NULL) {
        SDL_Log("Couldn't allocate data for dynamic array: %s\n", SDL_GetError());
        return array;
    }

    array.data = data;
    array.length = 0;
    array.capacity = 1;
    array.element_size = element_size;
    return array;
}

void
dyn_array_add(Dyn_Array* array, const void* element)
{
    if (array->length == array->capacity) {
        void* data = array->data;
        size_t new_capacity = array->capacity * 2; 
        array->data = SDL_realloc(array->data, new_capacity * array->element_size);
        array->capacity = new_capacity;
    }

    char* dest = array->data + array->length * array->element_size;
    memcpy(dest, element, array->element_size);
    array->length++;
}

void*
dyn_array_get(Dyn_Array array, size_t index)
{
    if (index >= array.length) return NULL;
    return (void*) array.data + index * array.element_size;
}

void
dyn_array_drop(Dyn_Array* array)
{
    SDL_free(array->data);
    array->length = 0;
    array->capacity = 0;
    array->element_size = 0;
}