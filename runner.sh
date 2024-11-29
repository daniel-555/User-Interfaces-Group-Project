#!/bin/sh

rm -rf build
mkdir build
cd build
cmake ..
make quaketool
exec ./quaketool
