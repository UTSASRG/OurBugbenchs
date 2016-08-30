#!/bin/bash
THREADS=2
#SEARCH_DIR=/usr/share
SEARCH_DIR=/home/hongyuliu/workspace/apps4doubletake/deadlock/LockAnalyzer
REGEXP=deadlock
TMP_FILE=tmp1

echo "The search directory contains `find $SEARCH_DIR -type f -print | wc -l` files."
rm -f $TMP_FILE results1.txt results2.txt

# warming the cache...
printf "warming up... "
TGLIMIT=$THREADS time -f "%U %S" ./tgrep -B $REGEXP $SEARCH_DIR >OUT.vanilla
sort OUT.vanilla > SORT
mv -f SORT OUT.vanilla

#
#RESULTS=results1.txt
#rm -f $RESULTS 
#for ((i=1 ; i <= $THREADS  ; i*=2)) do
#  printf "vanilla, $i thread(s) "
#  TGLIMIT=$i time -o $TMP_FILE -f "%U %S %e" ./tgrep -B $REGEXP $SEARCH_DIR >OUT.$i
#  cat $TMP_FILE
#  sort OUT.$i > SORT
#  mv -f SORT OUT.$i
#  awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' $TMP_FILE >> $RESULTS
#  diff -q OUT.$i OUT.vanilla && rm -f OUT.$i
#  rm -f $TMP_FILE
#done

#
#RESULTS=results2.txt
#rm -f $RESULTS 
#for ((i=1 ; i <= $THREADS  ; i*=2)) do
#  printf "modified, $i thread(s) "
#  TGLIMIT=$i time -o $TMP_FILE -f "%U %S %e" ./tgrep_mod -B $REGEXP $SEARCH_DIR >OUT.MOD.$i
#  cat $TMP_FILE
#  sort OUT.MOD.$i > SORT
#  mv -f SORT OUT.MOD.$i
#  awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' $TMP_FILE >> $RESULTS
#  diff -q OUT.MOD.$i OUT.vanilla && rm -f OUT.MOD.$i
#  rm -f $TMP_FILE
#done

