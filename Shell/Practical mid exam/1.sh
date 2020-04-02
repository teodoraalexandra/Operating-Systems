#!/bin/bash

files=0
for filename in `find $1`; do
  if [ -f $filename ]; then
    if [[ $filename =~ \.c$ ]]; then
      nr_lines=`cat $filename | wc -l`
      if [ $nr_lines -gt 20 ]; then
        echo $filename, $nr_lines 
      fi
      $files=`expr $files + 1`
      if [ $files -eq 5 ]; then
        break
      fi
    fi
  fi
done

#!/bin/bash

for filename in `find . -name '*.log'`; do
cat $filename | sort > sortedaux.log
`mv sortedaux.log $filename`
done

#!/bin/bash

for filename in `find $1`; do
if [ -L $filename ]; then
if ! [ -e $filename ]; then
echo $filename "- The file that this file is pointing does not exist anymore :("
fi
fi
done

#!/bin/bash

while `true`; do
processes=`ps | awk '{ print $1" "$4 }' | grep -v '\(CMD\)\|\(5.sh\)'`

for dang_proc in $@; do
if [[ $processes == *$dang_proc* ]]; then
pid=`ps | grep $dang_proc | awk '{ print $1 }'`
kill $pid
fi
done
sleep 2
done


