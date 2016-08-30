#!/bin/bash

echo "---------compile SQLite"

cd /home/zjp/projects/Applications/SQLite-3.3.3
./configure --enable-threadsafe
make
cd deadlock_test
make

echo

#LD_PRELOAD=/home/zjp/projects/LockAnalyzer/source/liblockanalyzer.so ./deadlock
time ./deadlock
time ./odeadlock

