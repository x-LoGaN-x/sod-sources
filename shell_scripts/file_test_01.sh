#!/bin/bash

# Dichiarazione della variabile
file="./file"

# Controllo dell'eseistenza del file
if [ -e $file ]; then
	echo "Il file $file esiste"
else
	echo "Il file $file non esiste"
fi
