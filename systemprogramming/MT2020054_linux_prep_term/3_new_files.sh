#!/bin/bash

for i in "$@"
do
  touch $i
  echo "file $1 created.."
done