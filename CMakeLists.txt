cmake_minimum_required(VERSION 3.16)

project(myCompiler)

add_definitions("-g -Wall")

include_directories(include/front_end)
include_directories(include/tools)

aux_source_directory(src/front_end FRONT_SRCS)
add_library(frontlib ${FRONT_SRCS})

aux_source_directory(src/tools TOOL_SRCS)
add_library(toollib ${TOOL_SRCS})

add_executable(SyntaxTree test/SyntaxTreeTest.c)
target_link_libraries(SyntaxTree frontlib toollib)

add_executable(HashTest test/HashTest.c)
target_link_libraries(HashTest toollib)


add_executable(IRTest test/IRTest.c)
target_link_libraries(IRTest frontlib toollib)
