#!/bin/sh

cd ./nginx
time=$1
for i in $(seq 1 $time)
do

  ./sbin/nginx

  python ../test/hb-test.py localhost

  ./sbin/nginx -s stop

  echo "Running $i times"
done

