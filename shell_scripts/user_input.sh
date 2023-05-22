#!/bin/bash

echo "Ciao, scrivimi una parola..."
read  word
echo "La parola che hai scritto è \"$word\""

echo "Adesso puoi scrivermi due parole?"
read word1 word2
echo "Ecco quello che mi hai scritto: \"$word1\" \"$word2\""

echo "Che ne pensi dello scripting bash?"
# Se non si definisce una variabile dopo il comando read
# in automatico l'input verrà salvato all'interno della
# variabile $REPLY
read
echo "Hai detto $REPLY, sono contento di sentirtelo dire"

echo "Quali sono i tuoi colori preferiti?"
# Con l'opzione -a il comando read salverà i dati immessi in un array
read -a colours
echo "Anche i miei colori preferiti sono ${colours[0]}, ${colours[1]} e ${colours[2]} :D"
