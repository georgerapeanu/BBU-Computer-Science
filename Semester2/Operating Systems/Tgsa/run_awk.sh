awk -F~ -v threshold=$1 -f awk.awk awk_file
