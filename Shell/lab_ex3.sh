#!/bin/bash

for filename in `find . -name "*.txt"`
do
  if [ -f $filename ]
  then

     if grep "cat" $filename 
     then
         echo $filename
     fi
  fi
done
