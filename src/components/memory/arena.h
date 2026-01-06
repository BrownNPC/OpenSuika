#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const auto ARENA_DEFAULT_ALIGNMENT = 8;
// double the size when growing
static const auto ARENA_GROW_FACTOR = 2;

typedef struct Arena {
  uint8_t *buffer; // pointer to memory block
  size_t size;     // total allocated size
  size_t offset;   // current bump offset
} Arena;
static size_t ___align_up(size_t offset, size_t alignment) {
  return (offset + alignment - 1) & ~(alignment - 1);
}
static inline Arena *NewArena(size_t initial_size) {
  Arena *a = malloc(sizeof(Arena));
  if (!a)
    return NULL;

  a->buffer = malloc(initial_size);
  if (!a->buffer) {
    free(a);
    return NULL;
  }

  a->size = initial_size;
  a->offset = 0;
  return a;
}
static inline int ___arena_grow(Arena *a, size_t min_additional_size) {
  size_t new_size = a->size * ARENA_GROW_FACTOR;
  while (new_size < a->offset + min_additional_size) {
    new_size *= ARENA_GROW_FACTOR; // ensure it’s enough
  }

  uint8_t *new_buffer = realloc(a->buffer, new_size);
  if (!new_buffer)
    return 0; // failed

  a->buffer = new_buffer;
  a->size = new_size;
  return 1; // success
}
static inline void *Arena_Alloc(Arena *a, size_t n) {
  size_t aligned_offset = ___align_up(a->offset, ARENA_DEFAULT_ALIGNMENT);

  // Grow if needed
  if (aligned_offset + n > a->size) {
    if (!___arena_grow(a, n))
      return NULL; // fail if grow fails
    aligned_offset = ___align_up(a->offset, ARENA_DEFAULT_ALIGNMENT);
  }

  void *ptr = a->buffer + aligned_offset;
  a->offset = aligned_offset + n;
  return ptr;
}
static inline void Arena_Reset(Arena *a) {
  a->offset = 0; // reuse the memory
}

static inline void Arena_Destroy(Arena *a) {
  if (!a)
    return;
  free(a->buffer);
  free(a);
}
