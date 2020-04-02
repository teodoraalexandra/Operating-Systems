#!/bin/bash

sum=0
for number in $*
	do
		sum=$(($sum+$number))
	done

echo "Sum of command line arguments $sum."

sum2=0
n=1
while [ $n -ne 0 ]
do
	read -p "Enter a number: " n
	sum2=$(($sum2+$n))
done

echo "Sum of read arguments $sum2."		
