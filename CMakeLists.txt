cmake_minimum_required(VERSION 3.12)
project(Workbench)

set(CMAKE_CXX_STANDARD 14)

add_executable(Workbench main.cpp BST.h NodeData.h TreeSVG.h tests.h tests.cpp ExampleStruct.h)