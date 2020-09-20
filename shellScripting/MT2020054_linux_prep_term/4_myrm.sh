#!/bin/bash

if [ ! -d .recyclebin ]
  then mkdir .recyclebin
fi

read -p "Enter a file name to delete: " name
mv $name .recyclebin/
pwdVar=$(pwd)
echo "File delete... You can restore it from $pwdVar/.recyclebin/"