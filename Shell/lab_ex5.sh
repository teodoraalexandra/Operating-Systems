#!/bin/bash
a=$1
b=$2
function prime() 
{
	for((i=a; i<=b; i++))
	do
		echo "$i"
		if [ "$i" == "1" ]
		then 
			echo '$number is prime'
		fi

		for((cout=2; cout<i; cout++))
		do
			if [ 'expr $i % $cout' == 0 ] 
			then 
				echo '$i is a prime number'
			fi
		done
	done
}

prime "$2";



	
