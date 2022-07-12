#!/bin/bash

min=-1
found=0

while [ $# -gt 0 ] ; do
    
    if [ -d $1 ] ; then
        files=$(ls -a $1 | grep -E "^[.][^.]")
        for file in $files; do
            if [ -f "$1/$file" ] ; then
                if ls -l "$1/$file" | grep -q -E "^.{4}r"; then
                    echo "$file from directory $1"
                fi
            fi
        done
    elif echo $1 | grep -q -E "^[+-]?[0-9]+$" ; then 
        if [ $found -eq 0 ] || [ $min -gt $1 ] ; then
            found=1
            min=$1
        fi
    else 
        echo "Argument $1 is neither directory or number" 1>&2
    fi
    
    shift 1
done

if [ $found -eq 0 ] ; then
    echo "No integer was present, so minimum cannot be determined" 1>&2
else 
    echo "Minium is $min"
fi

