#!/bin/bash
# Programma principale

ver=0.0.1

function help {
   # Visualizzazione dell'help
   echo "Piccola descrizione delle funzionalità dello script."
   echo
   echo "Sintassi: options_01.sh [-h|V]"
   echo
   echo "Opzioni:"
   echo "h     Visualizza questo help."
   echo "V     Visualizza la versione dello script."
   echo
}

# Processamento delle opzioni

# Lettura delle opzioni
while getopts ":hV" option; do
   case $option in
      h) # Visualizzazione dell'help
         help
         exit;;
      V) # Visualizzazione della versione dello script
         echo ver. $ver
         exit;;
     \?) # Opzione non valida
         echo "Opzione -$OPTARG non valida"
         exit;;
   esac
done

echo "Hello world!"
