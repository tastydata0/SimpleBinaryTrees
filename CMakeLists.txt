cmake_minimum_required(VERSION 3.5)

project(SimpleBinaryTrees LANGUAGES C)

add_executable(SimpleBinaryTrees sources/Tree.c include/Tree.h sources/main.c sources/Interpreter.c include/Interpreter.h)
target_include_directories(${PROJECT_NAME} PRIVATE .)
