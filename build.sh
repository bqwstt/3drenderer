#!/bin/bash

CC=gcc
CFLAGS="-Wall -std=c99 -g -O0"
SDLFLAGS="-lSDL3 -Wl,-rpath,@executable_path/lib"
ENTRY=main.c
EXE=3d

set -x

$CC $ENTRY $CFLAGS -L./lib $SDLFLAGS -o $EXE