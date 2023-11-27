#!/bin/bash
if [ ! -d build ]; then
    mkdir build
fi

if [ ! -d build/bin ]; then
    mkdir build/bin
fi

if [ ! -d build/lib ]; then
    mkdir build/lib
fi

if [ ! -d build/source ]; then
    mkdir build/source
fi

if [ ! -d build/include ]; then
    mkdir build/include
fi

if [ "$(ls -A build/lib)" ]; then
    rm build/lib/*
fi

if [ "$(ls -A build/bin)" ]; then
    rm build/bin/*
fi

if [ "$(ls -A build/source)" ]; then
    rm build/source/*
fi

if [ "$(ls -A build/include)" ]; then
    rm build/include/*
fi

flex --outfile=build/source/lexer.cpp --header-file=build/include/lexer.hpp source/tokens.l
bison --output=build/source/parser.cpp --header=build/include/parser.hpp source/grammar.y
clang++ -g -o build/bin/compiler \
    source/main.cpp build/source/lexer.cpp build/source/parser.cpp \
    source/Ast/*.cpp \
    -std=c++20 -Wall -pedantic -I build/include -I source/Ast

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
    ./build/bin/compiler input/test0.txt
