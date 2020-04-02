#!/bin/bash

for filename in `find . -name "*.txt"`
do
	if [ -f $filename ] 
	then
		for val in `cat $filename|grep "^[1-9][0-9]\{3,\}$"`
		do		
			if [ $val -ge 1000 ]
			then
				echo $val
			fi
		done
	fi
done
