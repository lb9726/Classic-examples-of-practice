#!/bin/bash

isRunnian()
{
	echo "请输入年份"
	read year
	let "y1 = $year % 4"
	let "y2 = $year % 100"
	let "y3 = $year % 400"
#	let "leap = 3"
	if [ ! "$y1" -eq 0 ]
		then
			leap=0
	elif [ ! "$y2" -eq 0 ]
		then
			leap=1
	elif [ "$y3" -eq 0 ]
		then 
			leap=1
	else
		leap=0
	fi
	
	if [  "$leap" -eq 1 ]
		then
			echo "$year is a leap year"
	else
		echo "$year is not a leap year"
	fi		
}

isRunnian












