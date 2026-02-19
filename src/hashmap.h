// Needed a hashmap for another project of mine so here goes

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define LOAD_FACTOR 0.7
#define INITIAL_CAPACITY 16

// -------------- NECESSARY DATA STRUCTURES ----------------
typedef enum state{
    EMPTY,
    OCCUPIED,
    DEAD
} state;

typedef struct pair {
  char *key;
  int value;
} pair;

typedef struct map {
  pair *entries;
  size_t capacity;
  size_t size;
} map;


// ---------- HASH -----------
static inline uint64_t hash (const char* key);


// -------------- INTERNAL HELPERS ----------------
static inline uint64_t _index(uint64_t hash, size_t capacity) {
  return hash & (capacity - 1); // capacity must always be a power of 2
}

static void _resize(map *hmap, size_t new_capacity);



//-------------- EXTERNAL FUNCTIONS -----------------
// create
static inline map *map_init(void);
// free
static inline void map_free(map *hmap);


// insert
static inline void put(map *hmap, const char *key, int value);
// search
static inline int search(const map *hmap, const char *key);
// remove
static inline void delete (map *hmap, const char *key);



// ----------- RESIZE -------------
static void resize(map *hmap, size_t new_capacity) {
  pair *old = hmap->entries;
  size_t old_capacity = hmap->capacity;

  hmap->entries = calloc(new_capacity, sizeof(pair));
  hmap->capacity = new_capacity;
  hmap->size = 0;

  for (size_t idx = 0; idx < old_capacity; idx++) {
    put(hmap, old[idx].key, old[idx].value);
    free(old[idx].key);
  }

  free(old);
};




#endif
