cmake_minimum_required(VERSION 3.10)

project(G_4_file VERSION 1.0 LANGUAGES C)

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
