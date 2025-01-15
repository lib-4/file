#ifndef G_0_ALLOCATOR_SHORTCUT_H
#define G_0_ALLOCATOR_SHORTCUT_H

#include "allocator_functions.h"

typedef g_0_allocator_t g_allocator_t;

#define g_alloc g_0_allocator_alloc
#define g_expand g_0_allocator_expand
#define g_dealloc g_0_allocator_dealloc

#endif
