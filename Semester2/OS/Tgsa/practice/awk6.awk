BEGIN{
  cnt_fields=0
  cnt_lines=0
}


NF % 2 == 1{
  fields[cnt_fields++] = $((1 + NF) / 2)
}
NF >= 2{
  lines[cnt_lines++] = NR
}

END{
  print "Middle fields are "
  for(field = 0;field < cnt_fields;field++){
    print fields[field]
  }
  print "lines with minimum 2 words are "
  for(line=0;line < cnt_lines;line++){
    print lines[line]
  }
}
