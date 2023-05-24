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
   echo "h, --help      Visualizza questo help."
   echo "n, --name=...  Specifica il nome della persona che vuoi salutare."
   echo "s, --sec=...   Specifica il cognome della persona che vuoi salutare."
   echo "V              Visualizza la versione dello script."
   echo
}

function die {
   echo "$*" >&2
   exit 2
}

function needsArg {
   if [ -z "$OPTARG" ]; then
      die "Nessun argomento per l'opzione --$option"
   fi
}

# Processamento delle opzioni

optSpec=":hn:s:V-:"

# Lettura delle opzioni
while getopts "$optSpec" option; do

#    echo "L'opzione è "$option" mentre il parametro è "$OPTARG""
   if [[ "$option" = "-" ]]; then
      echo "$OPTARG"
      option="${OPTARG%%=*}"     # extract long option name
      OPTARG="${OPTARG#$option}"    # extract long option argument (may be empty)
      OPTARG="${OPTARG#=}"       # if long option argument, remove assigning `=`
   fi

#   echo "L'opzione è \""$option"\", mentre il parametro è "$OPTARG""
   case $option in
      h | help)   # Visualizzazione dell'help
                  help
                  exit;;
      n | name)   # Gestione del nome
                  echo $OPTARG
                  needsArg
                  name=$OPTARG;;
      s | sec)    # Gestione del cognome
                  echo $OPTARG
                  needsArg
                  surname=$OPTARG;;
      V)          # Visualizzazione della versione dello script
                  echo ver. $ver
                  exit;;
      \:)         # Opzione non valida
                  die "L'opzione -$OPTARG necessita di un argomento"
                  exit;;
      ??*)        # Opzione non valida
                  die "Opzione --$OPTARG non valida"
                  exit;;
      ?)          # Opzione non valida
                  die "Opzione -$OPTARG non valida"
                  exit;;
   esac
done

if [[ -n $name || -n $surname ]]; then
   echo "Hello $name $surname!"
else
   echo "Hello world!"
fi
