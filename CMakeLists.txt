cmake_minimum_required(VERSION 3.10)

project(G_4_file VERSION 1.0 LANGUAGES C)

if(NOT WIN32)
  add_definitions(-D_FILE_OFFSET_BITS=64)

  include(CheckTypeSize)
  check_type_size("off_t" OFF_T_SIZE)
  if (OFF_T_SIZE LESS 8)
    message(FATAL_ERROR "off_t is less than 64 bits")
  endif()
endif()

set(SOURCES
  src/file.c
)

add_library(G_4_file STATIC ${SOURCES})
set_target_properties(G_4_file PROPERTIES
  OUTPUT_NAME "-4_file"
)

target_include_directories(G_4_file
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external_include
)

install(TARGETS G_4_file
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(
  FILES
    include/-4_file.h
  DESTINATION
    include
)

install(
  FILES
    include/-4/file_functions.h
    include/-4/file_shortcut.h
    include/-4/file_types.h
  DESTINATION
    include/-4
)
