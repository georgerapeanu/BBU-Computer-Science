BEGIN{
  cnt_min = -1;
  cnt_max = -1;
  len_min = 0;
  len_max = 0;
  sum_words = 0;
}

NF > cnt_max || cnt_max == -1{
  cnt_max = NF
  len_max = 0;
}

NF < cnt_min || cnt_min == -1{
  cnt_min = NF
  len_min = 0;
}


NF == cnt_max{
  max_lines[len_max] = $0
  len_max++
}

NF == cnt_min{
  min_lines[len_min] = $0
  len_min++
}

{
  sum_words += NF
}

END{
  print "Max lines"
  for(i = 0;i < len_max;i++){
    print max_lines[i]
  }
  print "Min lines"
  for(i = 0;i < len_min;i++){
    print min_lines[i]
  }
  print "Average " sum_words / NR
}
