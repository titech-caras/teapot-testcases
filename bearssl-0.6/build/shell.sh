#!/bin/bash
#dir = ./mycorpus
for i in `ls queue`
do 
  echo ${i}
  ./testcrypto ./queue/${i}
done
