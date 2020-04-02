#!/bin/bash

for filename in `find . -name "*.c"`
do
	sort < $filename
	sort > $filename
done
