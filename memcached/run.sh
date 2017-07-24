#!/bin/sh

time=$1
for i in $(seq 1 $time)
do

  nohup ./bin/memcached -l 192.168.1.2 -S -p 11211 -v -t 16 >> ./memcached.log 2>&1 &

  sleep 1

  python ./tests/poc_sasl.py 192.168.1.2 11211

  pkill memcached

  echo "Running $i times"
done

