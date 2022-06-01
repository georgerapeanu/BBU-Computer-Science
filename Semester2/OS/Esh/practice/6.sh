#!/bin/bash

data=""
while [ $# -gt 0 ] ; do
  if cat /etc/passwd | awk -F: '{print $1}' | grep -q $1; then
    homedir=$(cat /etc/passwd | awk -F: '{print $1":"$6}' | grep -E "^$1" | awk -F: '{print $2}')
    if find $homedir > /dev/null 2> /dev/null; then
      find $homedir
    else
      echo "Not enough rights"
    fi
    finger $1
  fi
  shift 1
done
