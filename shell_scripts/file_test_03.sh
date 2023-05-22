#!/bin/bash

# Dichiarazione della variabile
file="./file"

# Attesa in sleep finché il file non esiste
# Il ! serve a negare il risultato del test
while [ ! -e $file ]; do
    # Sleep until file does exists/is created
    echo "$file non esiste, mi metto in sleep!"
    sleep 1
done
