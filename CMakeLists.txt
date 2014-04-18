cmake_minimum_required(VERSION 2.8)

project(simple)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_executable(simple
    main.cpp
    token.hpp token.cpp
    lexer.hpp lexer.cpp
    ast.hpp ast.cpp
    parser.hpp parser.cpp
    astxml.hpp astxml.cpp
    codegen.hpp codegen.cpp)

add_custom_command(TARGET simple POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/test"
    $<TARGET_FILE_DIR:simple>)

# TODO: Do this properly with find_package and all
target_link_libraries(simple LLVM-3.4)
