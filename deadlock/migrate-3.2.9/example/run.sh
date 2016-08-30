#!/bin/bash
THREADS=16

rm -f tmp results1.txt results2.txt

for i in 1 4 8 16 
do
  printf "vanilla $i threads "
  nthreads=$i /usr/bin/time -f "%U %S %e" -o tmp echo Y | ./migrate-n parmfile.testml.$i > /dev/null 2> /dev/null
  cat tmp
  awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' tmp >> results1.txt
done

for i in 1 4 8 16 
do
  printf "modified $i threads "
  nthreads=$i /usr/bin/time -f "%U %S %e" -o tmp echo Y | ./migrate_mod parmfile.testml.$i > /dev/null 2> /dev/null
  cat tmp
  awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' tmp >> results2.txt
# diff -rq OUT-$i.modified/ OUT-$i.vanilla && rm -fr OUT-$i.modified
done

#./plot.sh results1.txt results2.txt
