awk 'BEGIN {sum_impar = 0;cnt_impar = 0} NF % 2 == 0 {print $1 + $NF} NF % 2 == 1 {cnt_impar++;sum_impar += $((NF + 1) / 2)} END {print "media imparelor este " sum_impar/cnt_impar}' awk_file 
