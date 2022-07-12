awk '{sum=0;for ( i=1; i <= NF; i++) sum += $i; if( NR % 2 == 0 ) {print sum} if( NR % 2 == 1 ) { print sum / NF } }' awk_file 

