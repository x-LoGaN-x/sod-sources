#!/bin/bash

# Dichiarazione della variabile choice
choice=0

echo "1. Bash"
echo "2. Scripting"
echo "3. Tutorial"
echo -n "Quale parola si desidera [1,2 o 3]? "

# Lettura della scelta dell'utente
read choice

# Valutazione della risposta mediante il costrutto case
case $choice in
    1) echo "Hai scelto la parola: Bash";;
    2) echo "Hai scelto la parola: Scripting";;
    3) echo "Hai scelto la parola: Tutorial";;
    *) echo "La selezione non è valida!";;
esac
