NF % 2 == 1{
  print NF
}

NF % 2 == 0{
  print $1 " " $NF
}
