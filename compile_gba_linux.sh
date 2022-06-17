#!/bin/bash

if [ -f lumagba.gba ]; then
    rm lumagba.gba
    rm lumagba.sav
    rm lumagba.ss*
fi

cd resources
./0construct.sh
cd ..

make clean && make -j4

if [ -f lumagba.gba ]; then
    # export LD_LIBRARY_PATH=/opt/Qt/5.15.2/gcc_64/lib
    mgba-qt lumagba.gba &
fi
