#!/bin/bash

# Dichiarazione delle variabili intere
NUM1=2
NUM2=1
if  [ $NUM1 -eq $NUM2 ]; then
	echo "I numeri sono uguali!"
elif [ $NUM1 -gt $NUM2 ]; then
	echo "NUM1 è maggiore di NUM2!"
else
	echo "NUM2 è maggiore di NUM1!"
fi
