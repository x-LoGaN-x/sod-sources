#!/bin/bash
#Dichiarazione della stringa str1
str1="Bash"
#Declare string str2
str2="Zsh"

if [ "$str1" = "$str2" ]; then
	echo "Le stringhe sono uguali"
else
	echo "Le stringhe non sono uguali"
fi
