#!/bin/sh
set -ex

cmake --build build --target sweeppp -j$(nproc)
./build/Debug/sweeppp