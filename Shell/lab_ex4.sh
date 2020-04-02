#!/bin/bash

user=$1
nr_files=0

if [ -f $user ] 
then
	echo "The name of the file is: " $user
	number_of_characters=`cat $user|wc -c`
	echo "Number of characters are: " $number_of_characters
	number_of_lines=`cat $user|wc -l`
	echo "Number of lines are: " $number_of_lines
elif [ -d $user ]
then
	echo "The name of the directory is: " $user
	for file in $user
	do
		nr_files=$(($nr_files+1))
	done
	echo "Number of files: " $nr_files
else 
	echo "No argument"
fi
