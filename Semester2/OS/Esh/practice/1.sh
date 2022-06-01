sum=0

while [ $# -gt 0 ] ; do 
  sum=$((sum + $(find $1 -type f | grep -c -E "\.c$")))
  shift 1
done

echo $sum
