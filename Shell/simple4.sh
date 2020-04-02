#!/bin/bash

number_of_lines=0
number_of_files_found=0

for filename in `find . -name "*.sh"`
do
	if [ -f $filename ]
	then
		number_of_lines=`cat $filename|wc -l`
		number_of_files_found=$(($number_of_files_found+1))
		if [ $number_of_lines -gt 10 ] 
		then
			echo $filename "has" $number_of_lines
		fi
	fi
	if [ $number_of_files_found -eq 5 ] 
	then
		break
	fi	
done

