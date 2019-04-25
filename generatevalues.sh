#!/bin/bash

echo "BEGINNING VALUE GENERATION"

echo "running make on each PRNG and the Test Suite"

echo "~Middle Square and LCG~"
make 

cd ./ThreeFry
echo "~ThreeFry~"
make
cd ..
cd ./TestSuite
echo "~TestSuite~"
make
cd ..

echo "Completed Makes"

echo "Generating values"
