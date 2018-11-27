bash#!/bin/bash
for i in {1..100}
do
  echo -ne "\rprogress: $i%"
  sleep 1
done
# print a new line
echo
