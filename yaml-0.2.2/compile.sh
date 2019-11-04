#!/bin/bash
./configure CFLAGS="-O0" CPPFLAGS="-O0" LDFLAGS="-static"
make clean && make