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

#!/bin/bash

count=0
for filename in `find . -name "*.c"`
do
if [ -f $filename ]
then
nr_lines=`cat $filename | wc -l`
if [ $nr_lines -gt 10 ]
then
echo $filename
count=$(($count+1))
fi
if [ $count -eq 10 ]
then
break
fi
fi
done

#!/bin/bash

w | tail -n +3 | cut -d" " -f1 | while read user ; do
name= finger $user | grep "Login: $user"
echo $name
done


