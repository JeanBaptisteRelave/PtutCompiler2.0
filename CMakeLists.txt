cmake_minimum_required(VERSION 3.5)

project(compiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(compiler main.cpp lexer.h lexer.cpp lexer.wjc parser.h parser.cpp parser.wjc)
