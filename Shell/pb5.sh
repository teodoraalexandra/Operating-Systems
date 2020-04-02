#!/bin/bash
count=0

for filename in `find . -name '*.c'`; do
	if [ -f $filename ]; then
		nr_lines=`cat $filename|wc -l`
		if [ $nr_lines -gt 10 ]; then 
			echo $filename
			count=$(($count + 1))
		fi
		if [ $count -eq 5 ]; then
			break
		fi
	fi
done
