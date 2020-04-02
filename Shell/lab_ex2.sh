#!/bin/bash

number_of_lines=0
number_of_txt=0

for filename in `find . -name "*.txt"`
do	
	if [ -f $filename ]
	then
		number_of_txt=$(($number_of_txt+1))
		current=`cat $filename|wc -l`
		number_of_lines=$(($number_of_lines+$current))
	fi	
done

average=0
average=$(($number_of_lines/$number_of_txt))
echo $average
echo "number of lines: $number_of_lines"
echo "number of txt found: $number_of_txt"
