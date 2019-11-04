#!/bin/bash
./configure
make
./c/fuzz/test_fuzzer.sh