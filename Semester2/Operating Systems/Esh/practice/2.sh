#!/bin/bash

if [ $# -lt 3 ] ; then
  echo "No"
  exit
fi

word=$1
n=$2
m=$3

shift 3

while [ $# -gt 0 ] ; do
  file=$1
  line=""
  ok=1
  for ((i=0;i < n;i++)) do
    read -r line || (ok=0 && break)
  done < $file
  if [ $ok -eq 0 ] ; then
    continue;
  fi

  fr=0
  for for_word in $line; do
    if [ "$for_word" == "$word" ] ; then
      fr=$(( $fr + 1))
    fi
  done
  if [ $fr -ge $m ] ; then
    echo $1
  fi
  shift 1
done

