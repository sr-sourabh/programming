#!/bin/bash

read -p "Enter a number to view its multiplication table: " num

for (( i = 1; i < 11; i++ )); do
    echo "$num x $i = $(($num*$i))"
done