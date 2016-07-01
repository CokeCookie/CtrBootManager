#!/bin/sh
mv build/screeninit.h screeninit.h &&
rm -rf build/* &&
rm -rf out/ &&
mv screeninit.h build/screeninit.h
