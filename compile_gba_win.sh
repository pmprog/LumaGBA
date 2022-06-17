#!/bin/bash
cd resources
./0construct.cmd
cd ..

make clean && make -j4
rm *.sav

if [ -f lumagba.gba ]; then
    /j/Emulators/Gameboy/mGBA/mGBA.exe lumagba.gba &
fi
