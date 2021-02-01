#!/bin/bash

who | awk -v loginName="$1"  '$0 ~ "^" loginName " " {print $3,$4}'