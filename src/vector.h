#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>


typedef struct vector vector;
//private static function for internal use, directly passing to prevent user use
static inline void _vec_grow (int** data, size_t size, size_t capacity, size_t elem_size);


//Declaring the at func ptr
typedef int (*vec_at_func)(const vector* vec, size_t idx);
//vector struct with metadata
typedef struct vector {
    int* data;
    size_t size;
    size_t capacity;
    size_t element_size;
    vec_at_func at;
} vector;
//Dealing with the function pointer
static inline int _vec_at_impl(const vector *vec, size_t idx) 
{
    if (idx >= vec->size) 
        return 0;               //change to assert    
    return vec->data[idx];
}
//Dealings over. I made it an offer it can't refuse.



//vector operations
static inline void vec_push (vector* vec, int value);
static inline void vec_replace (vector* vec, size_t index, int value);
static inline int vec_pop (vector* vec);

//getter
inline size_t get_size (vector* vec);

//basic functions
inline vector* vec_init (int* arr, size_t size, size_t elementSize);
inline void vec_free (vector* vec);


#endif
