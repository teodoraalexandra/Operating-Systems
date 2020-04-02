#!/bin/bash

cuvant=$1

maxim=`echo -n $1 | wc -m`

while [ $1 ] ; do
	cuvant=`sed "s|\([A-Z]\)||g"`
	nr_cuvinte=`echo $1 | wc -m`
	if [ $maxim -lt $nr_cuvinte ] ; then
		maxim=$(($nr_cuvinte))
	fi
	echo "Cuvantul: " $1 "are: " $nr_cuvinte " litere"
	shift 1
done

echo "Maximul de litere al parametrilor este: " $maxim
