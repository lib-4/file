#ifndef G_0_ALLOCATOR_FUNCTIONS_H
#define G_0_ALLOCATOR_FUNCTIONS_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#include "allocator_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void *g_0_allocator_alloc(g_0_allocator_t *self, size_t size);
void *g_0_allocator_expand(g_0_allocator_t *self, void *ptr, size_t size);
void g_0_allocator_dealloc(g_0_allocator_t *self, void *ptr);
void g_0_allocator_destroy_self(g_0_allocator_t *self);

#ifdef __cplusplus
}
#endif

#endif
