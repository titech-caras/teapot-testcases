#!/bin/bash
#dir = ./mycorpus
for i in `ls my_corpos`
do 
  echo ${i}
  ./test_htp ./my_corpos/${i}
done
