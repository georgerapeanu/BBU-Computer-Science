{
  for(i = 1;i <= NF;i++){
    fr[$i]++
  }
}

END{
  for(word in fr){
    print word ":" fr[word]
  }
}
