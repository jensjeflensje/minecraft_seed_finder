#!/bin/bash

cd cubiomes/
make libcubiomes
cd ..

gcc seed_find.c cubiomes/libcubiomes.a -fwrapv -lm -o seed_find