#!/bin/bash
#dir = ./mycorpus
for i in `ls out/queue`
do 
  echo ${i}
  ./parser ./out/queue/${i}
done
