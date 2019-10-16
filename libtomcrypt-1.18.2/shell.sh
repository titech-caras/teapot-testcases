#!/bin/bash
#dir = ./mycorpus
for i in `ls queue`
do 
  echo ${i}
  ./aes ./queue/${i}
done
