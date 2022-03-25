BEGIN{
  sum = 0
}

{
  print $1 + $(NF - 1) + $NF
  sum += $1
}

END{
  print sum / NR
}
