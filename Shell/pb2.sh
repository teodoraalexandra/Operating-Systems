#!/bin/bash

pentru_c=0

for filename in `find . -name "*.c"`
do
    if [ -f $filename ]
    then
	pentru_c=$(($pentru_c+1))
    fi
done

echo "extensii c: $pentru_c"

pentru_txt=0
for filename in `find . -name "*.txt"`
do
    if [ -f $filename ]
    then
        pentru_txt=$(($pentru_txt+1))
    fi
done

echo "extensii txt: $pentru_txt"

pentru_zip=0
for filename in `find . -name "*.zip"`
do
		pentru_zip=$(($pentru_zip+1))
done

echo "extensii zip: $pentru_zip"
