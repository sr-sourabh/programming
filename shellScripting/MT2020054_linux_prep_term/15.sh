#!/bin/bash

choice=-1

while [ $choice -ne 8 ]; do
    echo "**********SED MENU**********
          1. Find all lines containing pattern
          2. List lines not containing pattern
          3. Find lines starting and ending with some pattern
          4. Print lines in range
          5. Search file for pattern, replace
          6. Insert a string at begining of each line of file
          7. Insert a string at the end of each line of file
          8. Exit"
    read -p "Enter your choice: " choice

    case $choice in
    1)
      read -p "Enter the pattern: " pattern
      sed -n "/${pattern}/p" $1
      ;;
    2)
      read -p "Enter the pattern: " pattern
      sed "/$pattern/d" $1
      ;;
    3)
      read -p "Enter the start pattern: " startPattern
      read -p "Enter the end pattern: " endPattern
      sed -n "/^$startPattern.*$endPattern$/p" $1
      ;;
    4)
      read -p "Enter the start range of line: " beg
      read -p "Enter the end range of line: " end
      sed -n "${beg},${end}p" $1
      ;;
    5)
      read -p "Enter the pattern to be searched: " searchPat
      read -p "Enter the replace pattern: " replacePat
      sed "s/$searchPat/$replacePat/g" $1
      ;;
    6)
      read -p "Enter the string to inserted at beginning of each line: " str
      sed "s/^/$str/" $1
      ;;
    7)
      read -p "Enter the string to inserted at end of each line: " str
      sed "s/$/$str/" $1
      ;;
    8) exit
      ;;
    *) echo "Wrong choice please try again..."
      ;;
    esac
done