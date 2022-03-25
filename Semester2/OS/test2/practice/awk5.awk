BEGIN{
  cnt_words = 0
}


{
  cnt_words += NF
  for(i = 1;i <= NF;i++){
    fr[$i]++;
  }
}

END{
  print "Medium number of words " cnt_words / NR
  
  for(word in fr){
    if(fr[word] < cnt_words / NR){
      print word " with frequency " fr[word]
    }
  }

}

