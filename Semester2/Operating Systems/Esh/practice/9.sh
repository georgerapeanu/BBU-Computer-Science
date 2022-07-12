#!/bin/bash

while [ $# -gt 0 ] ; do
  for word in $(cat $1 | sed -E 's/([^02468]|^)(([1-9][0-9]*[02468])|0)([^02468]|$)/ \3 /g'); do
    echo $word
  done | awk '{
    for(i=1;i<=NF;i++){
      if($i ~ /^([1-9][0-9]*[02468])|0$/){
        if(!($i in fr)){
          fr[$i]=0
        }
        fr[$i]++
      }
    }
  }
  END{
    for(elem in fr){
      print elem " has frequency " fr[elem]
    }
  }'
  shift 1
done
