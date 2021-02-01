#!/bin/bash

df | awk -v fileSystem="$1" '$0 ~ "^" fileSystem " " {print system("du -h " $6)}'