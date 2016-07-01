#!/bin/sh
./clean.sh &&
cd build/ &&
cmake -DCMAKE_TOOLCHAIN_FILE=../DevkitArm3DS.cmake ../ &&
cmake --build . --target screeninit_a9lh &&
cmake --build . --target CtrBootManager_a9lh &&
mkdir ../out &&
mv CtrBootManager9.bin ../out/CtrBootManager9.bin
