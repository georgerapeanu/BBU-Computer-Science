#!/usr/bin/bash  

for x in `ls $1| grep -E "*.c$"`;do
  if test -f "$1/$x"; then
    awk 'BEGIN{s=0} $0 !~ /^[ \n\t]*$/{print $0;s = s + 1} END{print s}' $1/$x
    grep -E -v -c "^[ \t\n]*$" $1/$x
  fi
done
