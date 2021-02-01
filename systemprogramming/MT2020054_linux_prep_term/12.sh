#!/bin/bash

read -p "Enter the criteria to search: " search
if [[ $search == "IIT" ]]; then
    echo "NIT"
  elif [[ $search == "NIT" ]]; then
    echo "IIT"
  else
    echo "STDERR"
fi