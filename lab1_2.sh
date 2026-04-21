#!/bin/bash

num1=$1
num2=$2

if [ "$num1" -gt "$num2" ]; then
	echo "First parameter ($num1) more than second ($num2)!"
	echo "List of pseudonymous (alias) system"
	shopt -s expand_aliases
	source ~/.bashrc 2>/dev/null
	alias

else
	echo "Second parameter ($num2) more than first ($num1)!"
	script_name="$0"
	script_size=$(stat -c%s "$script_name")
	echo "Script name: $script_name"
	echo "Size of this script: $script_size"
fi
