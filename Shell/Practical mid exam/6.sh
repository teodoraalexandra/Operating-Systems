#!/bin/bash

cuvant=$1
number_of_letters=0
maxim=0

for parameter in $* 
do
	number_of_letters=`echo $parameter | sed 's/[A-Z]*//g' | wc -c`
	number_of_letters=$(($number_of_letters-1))
	if [ $maxim -lt $number_of_letters ]
	then 
		maxim=$(($number_of_letters))
	fi
	echo "Little letters of " $parameter ": " $(($number_of_letters))
done

echo "Maximul este: " $maxim
