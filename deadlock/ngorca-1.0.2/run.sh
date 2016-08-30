#!/bin/bash
THREADS=16

rm -f tmp results1.txt results2.txt

for ((i=16 ; i <= $THREADS ; i*=2)) do
  printf "vanilla $i threads "
  /usr/bin/time -f "%U %S %e" -o tmp ngorca/src/bin/ngorca -t$i -f \
    hashlist -l6 > /dev/null 2> /dev/null
  cat tmp
  awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' tmp >> results1.txt
done

#
#for ((i=1 ; i <= $THREADS ; i*=2)) do
#  printf "modified $i threads "
#  #LD_PRELOAD=./prof/gprof-helper.so /usr/bin/time -f "%U %S %e" -o tmp \
#  /usr/bin/time -f "%U %S %e" -o tmp \
#    ngorca/src/bin/ngorca_mod -t$i -f hashlist -l6 > /dev/null 2> /dev/null
#  cat tmp
#  awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' tmp >> results2.txt
#done
