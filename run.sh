#!/bin/bash

set -xe
CFLAGS="-Wall -Wextra -g`pkg-config --cflags raylib`"
LIBS="`pkg-config --libs raylib` -lraylib -lglfw -lm -ldl -lpthread"
# clang $CFLAGS -o p1 main.c $LIBS
clang $CFLAGS -o plot tinyexpr.c main.c $LIBS
./plot $1
