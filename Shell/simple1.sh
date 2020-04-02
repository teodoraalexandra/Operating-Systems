#!/bin/bash

nr_lines=0
filename=$1
if [ -f $filename ] 
then 
	nr_lines=`cat $filename | wc -l`
else 
	echo "This is not a file"
fi

echo "Number of lines of $filename is $nr_lines"
