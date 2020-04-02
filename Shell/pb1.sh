#!/bin/bash

inceput=$1
sfarsit=$2

while [ $inceput -le $sfarsit ] ; do
	ok=1
	expr=$((inceput/2))
	j=2
	while [ $j -le $expr ] ; do
		anatha=$((inceput%j))
		if [ $anatha -eq 0 ] ; then
			ok=0
		fi
		j=$((j+1))
	done
	if [ $ok -eq 1 ] ; then
		echo $inceput
	fi

	inceput=$((inceput+1))
done
