#!/bin/bash
# Programma principale

# Processamento delle opzioni

# Lettura delle opzioni
while getopts ":h" option; do
   case $option in
      h) # display Help
         echo "Richiamo della funzione Help"
         exit;;
   esac
done

echo "Hello world!"
