#!/bin/bash

#$1 is directory to be compressed
#$2 is the name to be given to compressed file
if [ -d $1 ]
then
  echo "Backing up $1..."
  if [[ $2 != *".tar.gz" ]]
  then
    set -- "$1" "${2}.tar.gz"
    echo "New file name will be $2 due to compatibility reasons"
  fi
  tar -zcvf $2 $1
  echo "Backup file $2 is created successfully..."
else
  echo "Directory with name $1 does not exists..."
fi