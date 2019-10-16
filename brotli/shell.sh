#!/bin/bash
#dir = ./mycorpus
for i in `ls mycorpus`
do 
  echo ${i}
  ./run_decoder ./mycorpus/${i}
done
