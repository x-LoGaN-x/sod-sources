#!/bin/bash
#Dichiarazione della stringa str1
str1="Bash"
#Declare string str2
str2="Zsh"

if [[ "$str1" > "$str2" ]]; then
	echo "${str1} è lessicograficamente più grande di ${str2}"
elif [[ "$str2" > "$str1" ]]; then
	echo "${str2} è lessicograficamente più grande di ${str1}"
else
    echo "Le stringhe sono uguali"
fi
