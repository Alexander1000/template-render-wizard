#!/bin/bash

# clear cache
rm -rf cmake-build-debug
rm -rf CMakeFiles
rm -f cmake_install.cmake
rm -f CMakeCache.txt
rm -f Makefile
rm -f template-render-wizard
rm -f template-render-wizard-cbp

cmake .
make
