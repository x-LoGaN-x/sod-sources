#!/bin/bash

# Dichiarazione della variabile
file="./file"

# Dichiarazione della variabile contenente il gruppo
# dell'utente che esegue lo script
group=$(id -ng)

# Controllo dell'eseistenza del file
if [[ -e $file ]]; then
	echo "Il file $file esiste"

    # Controllo file o directory
	if [[ -f $file ]]; then
        echo "$file è un file"
    else
        echo "$file è una directory"
    fi

    # Controllo del gruppo
    if [[ -G $file ]]; then
        echo "$file appartiene al gruppo $group"
    else
        echo "$file non appartiene al gruppo $group"
    fi
else
	echo "Il file $file non esiste"
fi
