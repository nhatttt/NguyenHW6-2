#!/bin/bash
#this is a script to build and run makeLED.cpp

g++ makeLED.cpp -o makeLED
./makeLED $1 $2
