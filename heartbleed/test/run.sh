#!/bin/sh

time=$1
for i in $(seq 1 $time)
do
  python hb-test.py localhost
  echo "Running $i times"
done

