#!/usr/bin/env sh
rm *.txt
./vnd n20c5_A.txt 1000 5 >> n20c5_A.txt &
./vnd n20c5_B.txt 1000 5 >> n20c5_B.txt &
./vnd n20c7_A.txt 1000 5 >> n20c7_A.txt &
./vnd n30c5_A.txt 1000 5 >> n30c5_A.txt &
./vnd n30c5_B.txt 1000 5 >> n30c5_B.txt &
./vnd n50c8_A.txt 1000 5 >>  n50c8_A.txt &
./vnd n50c8_B.txt 1000 5 >>  n50c8_B.txt &