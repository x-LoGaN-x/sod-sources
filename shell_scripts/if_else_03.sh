#!/bin/bash

# Dichiarazione della variabile choice
choice=0

echo "1. Bash"
echo "2. Scripting"
echo "3. Tutorial"
echo -n "Quale parola si desidera [1,2 o 3]? "

# Lettura della scelta dell'utente
read choice

# Blocchi annidati if/else
if [ $choice -eq 1 ] ; then
    echo "Hai scelto la parola: Bash"
elif [ $choice -eq 2 ] ; then
    echo "Hai scelto la parola: Scripting"
elif [ $choice -eq 3 ] ; then
    echo "Hai scelto la parola: Tutorial"
else
    echo "La selezione non è valida!"
fi
