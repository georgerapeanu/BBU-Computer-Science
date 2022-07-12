#!/bin/bash

if [ $# -lt 1 ] ; then
  echo "NOPE"
  exit
fi

word="$1"
shift 1

while [ $# -gt 0 ]; do
  count=0
  while read -r line; do
    for for_word in $line;do
      if [ $word == $for_word ] ; then
        count=$(($count + 1))
      fi
    done
  done < $1
  echo "Count for $1 is $count"
  shift 1
done
