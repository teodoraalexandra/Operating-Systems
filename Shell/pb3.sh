#!/bin/bash

w | tail -n +3 | cut -d" " -f1 | while read user ; do
	name= finger $user | grep "Login: $user" 
	echo $name
done
