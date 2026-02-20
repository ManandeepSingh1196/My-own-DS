#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdlib.h>

#include "vector.h"

typedef struct {
  vector *vec;
} stack;

static inline stack *stack_init(void) {
  stack *s = malloc(sizeof *s);
  if (!s)
    return NULL;
  s->vec = vec_init(NULL, 0);
  return s;
}

static inline void stack_push(stack *s, int value) { vec_push(s->vec, value); }

static inline int stack_pop(stack *s) { return vec_pop(s->vec); }

static inline int stack_top(stack *s) {
  if (s->vec->size == 0)
    return 0;
  return s->vec->data[s->vec->size - 1];
}

static inline int stack_empty(stack *s) { return s->vec->size == 0; }

static inline void stack_free(stack *s) {
  vec_free(s->vec);
  free(s);
}

#endif
