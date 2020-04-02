#!/bin/bash

cat who.fake | cut -d " " -f1 | while read user ; do
echo $user 
done

cat who.fake | awk '{print $2}' | while read user ; do
echo $user
done
