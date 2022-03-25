awk 'BEGIN{cnt_par=0;cnt_impar=0;cnt_linii_pare=0} {if( NR % 2 == 0 ) {cnt_par += NF;cnt_linii_pare++} if( NR % 2 == 1 ) { cnt_impar += NF} } END{print "total pare " cnt_par;print "mediu impare " cnt_impar / (NR - cnt_linii_pare) }' awk_file 

