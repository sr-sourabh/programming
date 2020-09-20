#!/bin/bash

hour=$(date '+%H')

if [ $hour -lt 12 ]; then
  echo "Good Morning"
elif [ $hour -lt 18 ]; then
  echo "Good Afternon"
else
  echo "Good Evening"
fi