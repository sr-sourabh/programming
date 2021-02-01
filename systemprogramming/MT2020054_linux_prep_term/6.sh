#!/bin/bash

choice=-1
echo "*************MENU*************
            1. ls
            2. pwd
            3. who
            4. Exit "
while [ $choice -ne 4 ]
do
  read -p "Enter you choice: " choice
  case $choice in
  1) ls
    ;;
  2) pwd
    ;;
  3) who
    ;;
  4) exit
    ;;
  *) echo "Wrong choice try again..."
    ;;
  esac
done
