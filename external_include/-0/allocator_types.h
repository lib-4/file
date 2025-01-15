#ifndef G_0_ALLOCATOR_TYPES_H
#define G_0_ALLOCATOR_TYPES_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stdbool.h>
#include <stddef.h>
#endif

typedef struct {
  void *(*alloc)(void *context, size_t size);
  void *(*expand)(void *context, void *ptr, size_t size);
  void (*dealloc)(void *context, void *ptr);
  void (*destroy_self)(void *context);
} g_0_allocator_v;

typedef struct g_0_allocator {
  const g_0_allocator_v *v;
  void *context;
} g_0_allocator_t;

#endif
