#!/bin/bash

# Dichiarazione della variabile choice
choice=0

PS3='Seleziona una parola: '

select word in "Bash" "Scripting" "Tutorial"
do
    case $word in
        "Bash") echo "Hai scelto la parola: Bash";;
        "Scripting") echo "Hai scelto la parola: Scripting";;
        "Tutorial") echo "Hai scelto la parola: Tutorial";;
        *) echo "La selezione non è valida!";;
    esac
    break
done
