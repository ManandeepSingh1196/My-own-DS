#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdlib.h>

#include "vector.h"

typedef struct queue {
  vector *vec;
  size_t head;
} queue;

static inline queue *queue_init(void) {
  queue *q = malloc(sizeof *q);
  if (!q)
    return NULL;

  q->vec = vec_init(NULL, 0);
  if (!q->vec) {
    free(q);
    return NULL;
  }

  q->head = 0;
  return q;
}

static inline int queue_empty(queue *q) { return q->head >= q->vec->size; }

static inline void queue_free(queue *q) {
  vec_free(q->vec);
  free(q);
}

static inline void queue_enqueue(queue *q, int value) {
  vec_push(q->vec, value);
}

static inline int queue_dequeue(queue *q) {
  if (queue_empty(q))
    return 0;

  int value = q->vec->data[q->head];
  q->head++;

  return value;
}

static inline int queue_front(queue *q) {
  if (queue_empty(q))
    return 0;

  return q->vec->data[q->head];
}

static inline void queue_compact(queue *q) {
  if (q->head == 0)
    return;

  size_t new_size = q->vec->size - q->head;

  for (size_t i = 0; i < new_size; i++)
    q->vec->data[i] = q->vec->data[i + q->head];

  q->vec->size = new_size;
  q->head = 0;
}

#endif
