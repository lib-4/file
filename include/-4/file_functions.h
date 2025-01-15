#ifndef G_4_FILE_FUNCTIONS_H
#define G_4_FILE_FUNCTIONS_H

#include "file_types.h"

#include <stddef.h>
#include <stdint.h>

#include "-0_allocator.h"
#include "-0_common.h"

#ifdef __cplusplus
extern "C" {
#endif

g_err_t g_4_file_write(g_4_file_t *file, const void *buffer, size_t length,
                       size_t *out_bytes_written);

g_err_t g_4_file_read(g_4_file_t *file, void *buffer, size_t length,
                      size_t *out_bytes_read);

g_4_file_t *g_4_file_open(g_0_allocator_t *allocator, const char *path,
                          int flags, int mode);

void g_4_file_close(g_4_file_t *file);

g_err_t g_4_file_unlink(const char *path);

g_err_t g_4_file_lseek(g_4_file_t *file, int64_t offset, int whence,
                       int64_t *new_position);

g_err_t g_4_file_truncate(const char *path, long length);

g_err_t g_4_file_rename(const char *old_path, const char *new_path);

g_err_t g_4_file_mkdir(const char *path, int mode);

g_err_t g_4_file_rmdir(const char *path);

#ifdef __cplusplus
}
#endif

#endif
