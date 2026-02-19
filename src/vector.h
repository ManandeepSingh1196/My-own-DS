#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>

typedef struct vector vector;
// Declaring the at func ptr
typedef int (*vec_at_func)(const vector *vec, size_t idx);
// vector struct with metadata
typedef struct vector {
  int *data;
  size_t size;
  size_t capacity;
  vec_at_func at;
} vector;
// Dealing with the function pointer
static inline int _vec_at_impl(const vector *vec, size_t idx) {
  if (idx >= vec->size)
    return 0; // change to assert
  return vec->data[idx];
}
// Dealings over. I made it an offer it can't refuse.

// private static function for internal use
static inline int _vec_grow(vector *vec) {
  size_t new_capacity = (vec->capacity == 0) ? 4 : vec->capacity * 2;

  int *new_data = realloc(vec->data, new_capacity * sizeof *new_data);

  if (!new_data)
    return 0; // Throw error, maybe

  vec->capacity = new_capacity;
  vec->data = new_data;
  return 1;
}

// vector operations
static inline void vec_push(vector *vec, int value) {
  if (vec->size == vec->capacity) {
    if (!_vec_grow(vec))
      return;
  }

  vec->data[vec->size++] = value;
}

static inline void vec_replace(vector *vec, size_t index, int value) {
  if (vec->size == 0)
    return;

  vec->data[index] = value;
}

static inline int vec_pop(vector *vec) {
  if (vec->size == 0)
    return 0; // Throw error

  return vec->data[--vec->size];
}

// getter
static inline size_t get_size(vector *vec) { return vec->size; }
// basic functions
static inline vector *vec_init(const int *arr, size_t size) {
  vector *vec = malloc(sizeof *vec);

  vec->data = NULL;
  vec->capacity = 0;
  vec->size = 0;

  if (size > 0) {
    for (size_t idx = 0; idx < size; idx++)
      vec_push(vec, arr[idx]);
  }

  return vec;
}

static inline void vec_free(vector *vec) {
  if (!vec)
    return;

  free(vec->data);
  free(vec);
}

static inline void reserve(vector *vec, size_t capacity) {
  if (capacity <= vec->capacity)
    return;

  int *data = malloc(capacity * sizeof *data);

  vec->data = data;
  vec->capacity = capacity;
  vec->size = 0;
}

#endif
