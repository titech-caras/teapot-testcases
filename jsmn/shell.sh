#!/bin/bash
for file in `ls $PWD/my_corpos`
do
  echo $file
  ./simple_fuzz ./my_corpos/$file
done
