#!/usr/bin/env sh
rm *.txt
./vnd n20c5_A.txt 1000 5 >> n20c5_A.txt 245 &
./vnd n20c5_B.txt 1000 5 >> n20c5_B.txt 180 &
./vnd n20c7_A.txt 1000 5 >> n20c7_A.txt 245 &
./vnd n30c5_A.txt 1000 5 >> n30c5_A.txt 665 &
./vnd n30c5_B.txt 1000 5 >> n30c5_B.txt 386 &
./vnd n50c8_A.txt 1000 5 >>  n50c8_A.txt 0 &
./vnd n50c8_B.txt 1000 5 >>  n50c8_B.txt 0 &