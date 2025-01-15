#ifndef G_4_THREAD_SHORTCUT_H
#define G_4_THREAD_SHORTCUT_H

#include "file_functions.h"

typedef g_4_file_t g_file_t;

#define g_file_write g_4_file_write
#define g_file_read g_4_file_read
#define g_file_open g_4_file_open
#define g_file_close g_4_file_close
#define g_file_unlink g_4_file_unlink
#define g_file_lseek g_4_file_lseek
#define g_file_truncate g_4_file_truncate
#define g_file_rename g_4_file_rename
#define g_file_mkdir g_4_file_mkdir
#define g_file_rmdir g_4_file_rmdir

#endif
