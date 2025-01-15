#include "-4_file.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "-0_allocator.h"
#include "-0_utils.h"

struct g_4_file {
  g_allocator_t *allocator;
#ifdef _WIN32
  HANDLE handle;
#else
  int fd;
#endif
};

g_err_t g_file_write(g_file_t *file, const void *buffer, size_t length,
                     size_t *out_bytes_written) {
#ifdef _WIN32
  DWORD result;
  if (!WriteFile(file->handle, buffer, (DWORD)length, &result, NULL)) {
    return true;
  }
  *out_bytes_written = result;
#else
  const ssize_t result = write(file->fd, buffer, length);
  if (result == -1) {
    return true;
  }
  *out_bytes_written = result;
#endif
  return false;
}

g_err_t g_file_read(g_file_t *file, void *buffer, size_t length,
                    size_t *out_bytes_read) {
#ifdef _WIN32
  DWORD result;
  if (!ReadFile(file->handle, buffer, (DWORD)length, &result, NULL)) {
    return true;
  }
  *out_bytes_read = result;
#else
  const ssize_t result = read(file->fd, buffer, length);
  if (result == -1) {
    return true;
  }
  *out_bytes_read = result;
#endif
  return false;
}

g_file_t *g_file_open(g_allocator_t *allocator, const char *path, int flags,
                      int mode) {
  g_file_t *file = g_alloc(allocator, sizeof(g_file_t));
  if (!file)
    return NULL;
  file->allocator = allocator;
#ifdef _WIN32
  DWORD access = 0, creation = 0;
  if (flags & G_FILE_FLAG_READ)
    access |= GENERIC_READ;
  if (flags & G_FILE_FLAG_WRITE)
    access |= GENERIC_WRITE;
  if (flags & G_FILE_FLAG_CREATE)
    creation = OPEN_ALWAYS;
  else
    creation = OPEN_EXISTING;

  file->handle =
      CreateFile(path, access, 0, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file->handle == INVALID_HANDLE_VALUE) {
    g_dealloc(allocator, file);
    return NULL;
  }
#else
  file->fd = open(path, flags, mode);
  if (file->fd < 0) {
    g_dealloc(allocator, file);
    return NULL;
  }
#endif
  return file;
}

void g_file_close(g_file_t *file) {
#ifdef _WIN32
  g_assert(CloseHandle(file->handle));
#else
  g_assert(close(file->fd) != -1);
#endif
  g_dealloc(file->allocator, file);
}

g_err_t g_file_unlink(const char *pathname) {
#ifdef _WIN32
  if (_unlink(pathname) == -1) {
    return true;
  }
#else
  if (unlink(pathname) == -1) {
    return true;
  }
#endif
  return false;
}

g_err_t g_file_lseek(g_file_t *file, int64_t offset, int whence,
                     int64_t *new_position) {
#ifdef _WIN32
  LARGE_INTEGER li;
  li.QuadPart = offset;
  li.LowPart = SetFilePointer(file->handle, li.LowPart, &li.HighPart, whence);
  if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
    return true;
  }
  *new_position = (int64_t)li.QuadPart;
#else
  const off_t result = lseek(file->fd, offset, whence);
  if (result == -1) {
    return true;
  }
  *new_position = result;
#endif
  return false;
}

g_err_t g_file_truncate(const char *pathname, long length) {
#ifdef _WIN32
  HANDLE handle = CreateFile(pathname, GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, NULL);
  if (handle == INVALID_HANDLE_VALUE)
    return true;

  LARGE_INTEGER li;
  li.QuadPart = length;
  if (SetFilePointerEx(handle, li, NULL, FILE_BEGIN) == 0 ||
      SetEndOfFile(handle) == 0) {
    CloseHandle(handle);
    return true;
  }
  CloseHandle(handle);
#else
  if (truncate(pathname, length) == -1) {
    return true;
  }
#endif
  return false;
}

g_err_t g_file_rename(const char *oldname, const char *newname) {
#ifdef _WIN32
  if (_rename(oldname, newname) == -1) {
    return true;
  }
#else
  if (rename(oldname, newname) == -1) {
    return true;
  }
#endif
  return false;
}

g_err_t g_file_mkdir(const char *pathname, int mode) {
#ifdef _WIN32
  if (_mkdir(pathname) == -1) {
    return true;
  }
#else
  if (mkdir(pathname, mode) == -1) {
    return true;
  }
#endif
  return false;
}

g_err_t g_file_rmdir(const char *pathname) {
#ifdef _WIN32
  if (_rmdir(pathname) == -1) {
    return true;
  }
#else
  if (rmdir(pathname) == -1) {
    return true;
  }
#endif
  return false;
}
