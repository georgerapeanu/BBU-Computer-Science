#!/bin/bash

if [ $# -lt 1 ] ; then
  echo "NO"
  exit
fi

n=$1
shift 1

while [ $# -gt 0 ] ; do
  for word in $(cat $1); do
    echo $word
  done | sort | uniq -c |awk -v n="$n" '$1>=n{print $2}'
  shift 1
done
