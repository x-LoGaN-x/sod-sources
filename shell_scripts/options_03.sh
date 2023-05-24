#!/bin/bash
# Programma principale

ver=0.0.1

function help {
   # Visualizzazione dell'help
   echo "Piccola descrizione delle funzionalità dello script."
   echo
   echo "Sintassi: options_01.sh [-h|n|V]"
   echo
   echo "Opzioni:"
   echo "h     Visualizza questo help."
   echo "n     Specifica il nome della persona che vuoi salutare."
   echo "V     Visualizza la versione dello script."
   echo
}

# Processamento delle opzioni

optSpec=":hn:V"

# Lettura delle opzioni
while getopts "$optSpec" option; do
   case "$option" in
      h) # Visualizzazione dell'help
         help
         exit;;
      n) # Gestione del nome
         name=$OPTARG;;
      V) # Visualizzazione della versione dello script
         echo ver. $ver
         exit;;
     \?) # Opzione non valida
         echo "Opzione -$OPTARG non valida" >&2
         exit;;
     \:) # Parametro mancante
         echo "L'opzione -$OPTARG richiede un parametro." >&2
         exit;;
   esac
done

if [[ -n $name ]]; then
   echo "Hello $name!"
else
   echo "Hello world!"
fi
