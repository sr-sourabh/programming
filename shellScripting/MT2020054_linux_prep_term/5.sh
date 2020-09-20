#!/bin/bash

read -p "Enter file name: " filename

if [ "$(find ./ -type f -name "$filename" | wc -l)"  -eq 0 ]
then
  echo "File with name : $filename does not exists"
fi