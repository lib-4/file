#ifndef G_0_UTILS_H
#define G_0_UTILS_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stdbool.h>
#include <stddef.h>
#endif

#include "-0/allocator_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void g_0_bzero(void *ptr, size_t size);
void *g_0_memdup(g_0_allocator_t *allocator, void *ptr, size_t size);
void *g_0_nonnull(void *ptr);
void g_0_assert(bool condition);

#ifdef __cplusplus
}
#endif

#endif
