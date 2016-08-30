#!/bin/bash

for (( i=0 ; i<150 ; i++ )); do wget -b http://localhost/largefile.bin; done;
