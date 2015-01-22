#!/bin/sh

echo "cleaning maintainer config files..."
rm -Rf -v aclocal.m4 autom4te.cache config.h.in* config.guess config.sub \
   install-sh ltmain.sh configure missing $(find . -iname Makefile.in) \
   build-aux/*

echo "cleaning default build directory..."
rm -Rf -v bin/*

echo "restoring default build directory..."
mkdir -p bin

echo "done"

