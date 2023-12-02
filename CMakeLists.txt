cmake_minimum_required(VERSION 3.20)
project(bootstrap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src/flex")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src/flex/include")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src/bison")
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src/bison/include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST
    NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})
string(REGEX MATCH "[0-9]+"
    LLVM_MAJOR_VERSION ${LLVM_PACKAGE_VERSION})
llvm_map_components_to_libnames(LLVM_LIBS
    "-${LLVM_MAJOR_VERSION}") # TODO fix

flex_target(LEXER "source/tokens.l"
    "${CMAKE_BINARY_DIR}/src/flex/lexer.cpp"
  DEFINES_FILE
    "${CMAKE_BINARY_DIR}/src/flex/include/lexer.hpp")
bison_target(PARSER "source/grammar.y"
    "${CMAKE_BINARY_DIR}/src/bison/parser.cpp"
  DEFINES_FILE
  "${CMAKE_BINARY_DIR}/src/bison/include/parser.hpp")
add_flex_bison_dependency(LEXER PARSER)

add_library(node STATIC
    "source/Node/Node.cpp")
target_include_directories(node
  PUBLIC
    "source/Node/include")

add_library(printer STATIC
    "source/Visitor/Printer/Printer.cpp")
target_include_directories(printer
  PUBLIC
    "source/Visitor/Printer/include")
target_link_libraries(printer
    node)

add_library(parser STATIC
    "${FLEX_LEXER_OUTPUTS}"
    "${BISON_PARSER_OUTPUTS}")
target_include_directories(parser
  PUBLIC
    "${CMAKE_BINARY_DIR}/src/flex/include"
    "${CMAKE_BINARY_DIR}/src/bison/include")
target_link_libraries(parser
    node)

add_executable(compiler
    "source/main.cpp")
target_link_libraries(compiler
    node
    printer
    parser)
