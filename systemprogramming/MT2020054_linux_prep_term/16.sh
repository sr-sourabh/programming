#!/bin/bash

choice=-1

while [ $choice -ne 8 ]; do
    echo "**********AWK MENU**********
          1. Display given file
          2. Print lines which match a pattern
          3. Print specific field of the file
          4. Format a given file with Name, Designation, Department and Salary headings and at the end of a file
print Report Generated
          5. Find the employees, who has id > 200
          6. Find the list of employees in Technology Department
          7. Print the number of employees in Technology Department
          8. Exit"
    read -p "Enter your choice: " choice

    case $choice in
    1)
      awk '$0' $1
      ;;
    2)
      read -p "Enter pattern to match: " pat
      awk -v pat="$pat" '$0 ~ pat' $1
      ;;
    3)
      read -p "Enter field to print: " field
      awk -v field="$field" '{print $field}' $1
      ;;
    4)
      awk 'BEGIN {print "Name\tDesignation\tDepartment\tSalary"} {print $2,"\t",$3,"\t",$4,"\t",$5} END {print "Report generated..."}' $1
      ;;
    5)
      awk '$1 > 200' $1
      ;;
    6)
      awk '$4 == "Technology"' $1
      ;;
    7)
      awk 'BEGIN {count = 0;} $4 == "Technology" {count++;} END {print "Number of employees in Technology Department: ",count;}' $1
      ;;
    8) exit
      ;;
    *) echo "Wrong choice please try again..."
      ;;
    esac
done