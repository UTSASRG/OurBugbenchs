#!/bin/bash
THREADS=16
TMP_FILE=tmp1
TIMES=7


RESULTS=results1.txt
TMP_RESULTS=tmp_results.txt

rm -f $RESULTS 
rm -f $TMP_RESULTS 
for ((i=1 ; i <= $THREADS  ; i*=2)) do
  sum1=0; sum2=0; sum3=0; sum4=0; sum5=0
  for ((j=1 ; j <= $TIMES  ; j+=1)) do
    printf "vanilla, $i thread(s) "
    /usr/bin/time -f "%U %S %e" -o $TMP_FILE ngorca/src/bin/ngorca -t$i -f \
      hashlist -l6 > /dev/null 2> /dev/null
    cat $TMP_FILE
    awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' $TMP_FILE >> $TMP_RESULTS
    rm -f $TMP_FILE
  done
  awk -v it=$i -v n="$TIMES" \
    '{sum1+= $2; sum2+=$3; sum3+=$4; sum4+=$5; sum5+=$6} \
     END{ print it " " sum1/n " " sum2/n " " sum3/n " " sum4/n " " sum5/n }' \
     $TMP_RESULTS >> $RESULTS
  echo "------------------------------------"  
  rm -f $TMP_RESULTS 
done

RESULTS=results2.txt
TMP_RESULTS=tmp_results.txt
rm -f $RESULTS 
rm -f $TMP_RESULTS 
for ((i=1 ; i <= $THREADS  ; i*=2)) do
  sum1=0; sum2=0; sum3=0; sum4=0; sum5=0
  for ((j=1 ; j <= $TIMES  ; j+=1)) do
    printf "modified, $i thread(s) "
    LD_PRELOAD=./prof/gprof-helper.so /usr/bin/time -f "%U %S %e" -o $TMP_FILE \
      hashlist -l6 > /dev/null 2> /dev/null
    cat $TMP_FILE
    awk -v it=$i '{print it, " ", $3, $1+$2, " ", $0;}' $TMP_FILE >> $TMP_RESULTS
    rm -f $TMP_FILE
  done
  awk -v it=$i -v n="$TIMES" \
    '{sum1+= $2; sum2+=$3; sum3+=$4; sum4+=$5; sum5+=$6} \
     END{ print it " " sum1/n " " sum2/n " " sum3/n " " sum4/n " " sum5/n }' \
     $TMP_RESULTS >> $RESULTS
  echo "------------------------------------"  
  rm -f $TMP_RESULTS 
done


