#!/bin/bash

for filename in `find .`
do	
	if [ -f $filename ] 
	then
		if grep -q "[0-9]" $filename
		then
			echo $filename
		fi
	fi
done
