#!/bin/bash
make CFLAGS="-O0"
make test CFLAGS="-O0"
mv test aes