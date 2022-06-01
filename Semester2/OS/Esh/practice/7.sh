#!/bin/bash 

if [ $# -lt 2 ] ; then
  echo "NO"
  exit
fi

n=$1
word=$2
shift 2

while [ $# -gt 0 ] ; do
  copy_n=$n
  echo "Processing $1"

  while read -r line;do
    if echo $line | grep -q -E "\<$word\>"; then
      copy_n=$(($copy_n-1))
    fi
    if [ $copy_n -eq 0 ] ; then
      echo $line
      break
    fi
  done < $1
  shift 1
done
