#!/bin/bash
# Programma principale

function help {
   # Visualizzazione dell'help
   echo "Piccola descrizione delle funzionalità dello script."
   echo
   echo "Sintassi: options_01.sh [-h]"
   echo
   echo "Opzioni:"
   echo "h     Visualizza questo help."
   echo
}

# Processamento delle opzioni

# Lettura delle opzioni
while getopts ":h" option; do
   case $option in
      h) # Visualizzazione dell'help
         help
         exit;;
   esac
done

echo "Hello world!"
