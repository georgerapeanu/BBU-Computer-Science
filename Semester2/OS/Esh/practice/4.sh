#!/bin/bash

if [ $# -lt 1 ] ; then
  echo "WRONG"
fi

n=$1
shift 1

output_buffer=""

while [ $# -gt 0 ] ; do
  echo "File $1 uses the following libraries:"
  cat $1 | grep -E '^[#]include *[<].*[>]$' | sed -E 's/^[#]include *[<](.*)[>]$/\1/'
  output_buffer="$output_buffer $(cat $1 | grep -E '^[#]include *[<].*[>]$' | sed -E 's/^[#]include *[<](.*)[>]$/\1/')"
  shift 1
done

echo $output_buffer | awk '{
  for(i = 1;i < NF;i++){
    print $i
  }
}' | uniq -c | sort -nr | head -n $n
