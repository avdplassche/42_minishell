export FILE_A="log/redirect/a.out"
export FILE_B="log/redirect/b.out"
export FILE_C="log/redirect/c.out"

cat < not_a_file
cat < not_a_file < fuck_off

echo "AAAA" > $FILE_A
grep . $FILE_A
echo "BBBB" > $FILE_A > $FILE_B
grep . $FILE_A log/redirect/b.out
echo "CCCC" >$FILE_A > $FILE_B
grep . $FILE_A log/redirect/b.out
echo >$FILE_A "DDDD" > $FILE_B
grep . $FILE_A log/redirect/b.out
echo > $FILE_A "EEEE" > $FILE_B
grep . $FILE_A log/redirect/b.out
> $FILE_A echo "FFFF" > $FILE_B
grep . $FILE_A log/redirect/b.out
> $FILE_A  > $FILE_B echo "GGGG" > $FILE_C 
grep . $FILE_A $FILE_B $FILE_C

export FILE_A="log/redirect/d.out"
export FILE_B="log/redirect/e.out"
export FILE_C="log/redirect/f.out"

grep o < Dockerfile > $FILE_B > $FILE_A > $FILE_C
cat < $FILE_A
grep o < $FILE_A
grep . $FILE_A $FILE_B
echo "YOLO" > $FILE_A >> $FILE_B 
grep . $FILE_A $FILE_B
echo "YALA" > $FILE_A >> $FILE_B >> $FILE_C
grep . $FILE_A $FILE_B $FILE_C
echo "HOHO" >> $FILE_A
grep . $FILE_A $FILE_B $FILE_C
grep "=" < Makefile > $FILE_A >> $FILE_B
grep . $FILE_A $FILE_B $FILE_C
grep "=" < Makefile >> $FILE_A > $FILE_B
grep . $FILE_A $FILE_B $FILE_C
grep "=" < dev.sh > $FILE_B >> $FILE_A
grep . $FILE_A $FILE_B $FILE_C

