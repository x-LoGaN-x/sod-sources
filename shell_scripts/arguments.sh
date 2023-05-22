#!/bin/bash
# Si possono utilizzare le variabili predefinite
# $1, $2, ..., $n per l'accesso ai vari argomenti

# Stampiamo a video i primi tre argmomenti passati
echo $1 $2 $3 ' -> echo $1 $2 $3'

# Si possono leggere tutti in un solo colpo utilizzando la variabile $@
# salvandone il contenuto all'interno di un array.
args=("$@")

# Stampiamo a video i primi tre argmomenti passati
echo ${args[0]} ${args[1]} ${args[2]} ' -> args=("$@"); echo ${args[0]} ${args[1]} ${args[2]}'

# Oppre possiamo stamparli tutti indistinamente utilizzando
# direttamente la variabile $@
echo $@ ' -> echo $@'

# Per conoscere il numero di argomenti che abbiamo passato al nostro script
# possiamo usare la variabile $#
echo Mi hai passato $# argomento/i ' -> echo Mi hai passato $# argomento/i'
