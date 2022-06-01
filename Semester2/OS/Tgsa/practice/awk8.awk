{
  cnt_bossi = 0
}

{
  print $1 " " $2 " " ($3 + $4 + $5) / 3
  if($3 + $4 + $5 >= 24){
    bossi[cnt_bossi++] = $1 " " $2
  }
}

END{
  for(boss = 0;boss < cnt_bossi;boss++){
    print bossi[boss]
  }
}
